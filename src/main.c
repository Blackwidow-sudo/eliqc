/*  Commandline Tool to create liquid recipes.
    Copyright (C) 2021  Merlin Cornehl

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>. */

/* Written May 2021 by Merlin Cornehl */

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

#include "functions.h"

int main(int argc, char *const argv[])
{
    // Template String for -h option
    const char HELP_TEMPLATE[] = "Usage: %s [OPTION]... [FILENAME]...\n"
                                "Create a Recipe for a Liquid with the given Ingredients.\n"
                                "Example: %s -f Bubblegum\n\n"
                                "Options:\n"
                                "  -f\tWrite recipe to textfile.\n"
                                "  -h\tDisplay this information.\n";

    bool f_flag = false; // -f write to file
    bool c_flag = false; // -c write to console
    char *desired_name;

    // Check for too many arguments
    if (argc == 1) 
        c_flag = true;
    else
        FAIL_IF_MSG((argc > 4), 7);

    // Formated Message for -h option (that gets printed)
    char HELP_MESSAGE[ (strlen(HELP_TEMPLATE) + strlen(argv[0])) - 1 ];
    sprintf(
        HELP_MESSAGE, 
        HELP_TEMPLATE,
        argv[0],
        argv[0]
    );

    // Handle command-line arguments
    int opt;
    while ( (opt = getopt(argc, argv, ":f:hc")) != -1 )
    {
        switch (opt)
        {
            case 'h':
                fputs(HELP_MESSAGE, stdout);
                exit(EXIT_SUCCESS);
                break;

            case 'c':
                c_flag = true;
                break;

            case 'f':
                f_flag = true;
                desired_name = optarg;
                break;

            case ':':
                fprintf(stderr, "Usage: %s [OPTION]... [FILENAME]...\nTry '%s -h' for more information.\n", argv[0], argv[0]);
                exit(EXIT_FAILURE);
                break;

            case '?':
                fprintf(stderr, "Error: %s -%c\n", strerror(22), optopt);
                exit(EXIT_FAILURE);
                break;
            
            default:
                fprintf(stderr, "Something went wrong when the program was parsing arguments.\n");
                exit(EXIT_FAILURE);
                break;
        }
    }

    // Handle extra arguments
    for(; optind < argc; optind++)
    {     
        printf("extra arguments: %s\n", argv[optind]);
    }

    // Get ingredients from User
    float desired_amount = get_float("Gewünschte Menge (ml): ");
    float nicotin_used = get_float("Verwendete Nicotinbasis (mg/ml): ");
    float desired_nicotin = get_float("Gewünschte Nicotinstärke (mg/ml): ");
    float desired_aroma = get_float("Gewünschter Aroma-Anteil (%%): ");
    float desired_pg = get_float("Gewünschter PG-Anteil (%%): ");
    float desired_vg = get_float("Gewünschter VG-Anteil (%%): ");

    // Create new liquid
    liquid_t newLiquid = {
        .title = (f_flag == true) ? desired_name : "",
        .amount = desired_amount,
        .nicotin = nicotin_used == desired_nicotin ? 0.00 : desired_amount / (nicotin_used / desired_nicotin),
        .aroma = desired_amount * (desired_aroma / 100),
        .pg = desired_amount * (desired_pg / 100) - newLiquid.nicotin - newLiquid.aroma,
        .vg = desired_amount * (desired_vg / 100)
    };

    if (f_flag)
        FAIL_IF(writeFile(&newLiquid) != 0);
    else if (c_flag)
        writeToConsole(&newLiquid);

    // Print Memory Usage
    /* struct rusage myusage;
    getrusage(RUSAGE_SELF, &myusage);
    printf("%ld\n", myusage.ru_maxrss); */

    exit(EXIT_SUCCESS);
}