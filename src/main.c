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

#include "functions.h"

// Template String for -h option
const string HELP_TEMPLATE = "Usage: %s [OPTION]... [FILENAME]...\nCreate a Recipe for a Liquid with the given Ingredients.\nExample: %s -f Bubblegum\n\nOptions:\n  -f\tWrite recipe to textfile.\n  -h\tDisplay this information.\n";

int main(int argc, char *const argv[])
{
    // Check for too many arguments
    if (argc > 4)
    {
        fprintf(stderr, "Error: %s\nUsage: %s <arg> <FILENAME>\n", strerror(7), argv[0]);
        exit(EXIT_FAILURE);
    }

    // Formated Message for -h option (that gets printed)
    char HELP_MESSAGE[(strlen(HELP_TEMPLATE) + strlen(argv[0])) - 1];
    sprintf(
        HELP_MESSAGE, 
        HELP_TEMPLATE,
        argv[0],
        argv[0]
    );

    bool writeToFile = false; // Is true when arg -f is present
    string gw_name; // Recipe title

    // Handle command-line arguments
    int opt;
    while ( (opt = getopt(argc, argv, ":f:h")) != -1 )
    {
        switch (opt)
        {
        case 'h':
            fputs(HELP_MESSAGE, stdout);
            exit(EXIT_SUCCESS);
            break;

        case 'f':
            writeToFile = true;
            gw_name = optarg;
            break;

        case ':':
            printf("Error: option -%c needs a filename. Use -h for help.\n", optopt);
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

    for(; optind < argc; optind++)
    {     
        printf("extra arguments: %s\n", argv[optind]);
    }

    // Get ingredients from user
    if (writeToFile == false)
        gw_name = get_string("Titel des Rezepts: ");
    
    float gw_menge = get_float("Gewünschte Menge (ml): ");
    float vw_nic = get_float("Verwendete Nicotinbasis (mg/ml): ");
    float gw_nic = get_float("Gewünschte Nicotinstärke (mg/ml): ");
    float gw_aroma = get_float("Gewünschter Aroma-Anteil (%%): ");
    float gw_pg = get_float("Gewünschter PG-Anteil (%%): ");
    float gw_vg = get_float("Gewünschter VG-Anteil (%%): ");

    // Create new liquid
    liquid_t newLiquid = {
        .name = gw_name,
        .amount = gw_menge,
        .nicotin = vw_nic == gw_nic ? 0.00 : gw_menge / (vw_nic / gw_nic),
        .aroma = gw_menge * (gw_aroma / 100),
        .pg = gw_menge * (gw_pg / 100) - newLiquid.nicotin - newLiquid.aroma,
        .vg = gw_menge * (gw_vg / 100)
    };

    if (writeToFile)
    {
        if (writeFile(&newLiquid) != 0)
        {
            perror("Could not write to file");
            exit(EXIT_FAILURE);
        }
    }
    else
        writeToConsole(&newLiquid);

    exit(EXIT_SUCCESS);
}