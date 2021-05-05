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

int writeFile(liquid_t *liquid)
{
    // Title of the Textfile
    char fileTitle[strlen(liquid->name) + 4];
    sprintf(fileTitle, "%s.txt", liquid->name);

    // Textfile for recepie
    FILE *recepie = fopen(fileTitle, "w");
    if (recepie == NULL)
        return errno;

    // Print recepie to textfile
    fprintf(
        recepie, 
        "%s:\n\tMenge: %.2fml\n\tNikotinbasis: %.2fml\n\tAroma: %.2fml\n\tPG: %.2fml\n\tVG: %.2fml\n", 
        liquid->name,
        liquid->amount,
        liquid->nicotin,
        liquid->aroma,
        liquid->pg,
        liquid->vg
    );

    fclose(recepie);

    return 0;
}

void writeToConsole(liquid_t *liquid)
{
    int breakLen = strlen(liquid->name) + 1;
    for (int i = 0; i < breakLen; i++)
    {
        if (i == breakLen - 1)
            printf("==\n");
        else
            printf("=");
    }

    printf(
        "%s:\n\tMenge: %.2fml\n\tNikotinbasis: %.2fml\n\tAroma: %.2fml\n\tPG: %.2fml\n\tVG: %.2fml\n",
        liquid->name,
        liquid->amount,
        liquid->nicotin,
        liquid->aroma,
        liquid->pg,
        liquid->vg
    );
}