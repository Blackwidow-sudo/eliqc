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

#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H 1

#include <cs50.h>

// Liquid Ingredients
typedef struct liquid
{
    string name;
    float amount, nicotin, aroma, pg, vg;
} liquid_t;

// Writes a liquid recepie to a textfile
int writeFile(liquid_t *liquid);

// Prints a liquid recepie to command-line
void writeToConsole(liquid_t *liquid);

#endif // _FUNCTIONS_H