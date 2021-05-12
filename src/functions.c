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
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "functions.h"

/* Print a given liquid to a file
    The function takes a liquid of type liquid_t and prints its contents to a file.
    The filename is built with liquid.title and ".txt".  */
int writeFile(liquid_t *liquid)
{
    // Title of the Textfile
    char fileTitle[strlen(liquid->title) + 4];
    sprintf(fileTitle, "%s.txt", liquid->title);

    // Create textfile with given fileTitle
    FILE *recepie = fopen(fileTitle, "w");
    if (recepie == NULL)
    {
        perror("Could not create file");
        return 1;
    }

    // Print recepie to textfile
    fprintf(
        recepie, 
        "%s:\n\tMenge: %.2fml\n\tNikotinbasis: %.2fml\n\tAroma: %.2fml\n\tPG: %.2fml\n\tVG: %.2fml\n", 
        liquid->title,
        liquid->amount,
        liquid->nicotin,
        liquid->aroma,
        liquid->pg,
        liquid->vg
    );

    fclose(recepie);

    return 0;
}

/* Print a given liquid to stdout */
void writeToConsole(liquid_t *liquid)
{
    // Create line of '='-Symbols to visually seperate user-input and output
    printf("========== Rezept ==========\n");

    // Print recipe to stdout
    printf(
        "\tMenge: %.2fml\n\tNikotinbasis: %.2fml\n\tAroma: %.2fml\n\tPG: %.2fml\n\tVG: %.2fml\n",
        liquid->amount,
        liquid->nicotin,
        liquid->aroma,
        liquid->pg,
        liquid->vg
    );
}


void manual_error(int errNo, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    printf("Error %d: %s\n", errNo, strerror(errNo));
    vfprintf(stderr, format, args);

    va_end(args);
}