#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_line(void);
char* read_line_f(FILE*);
void trim(char*);
void remove_all_spaces(char*);