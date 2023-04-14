#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// stdin에서 개행문자 전까지 문자 읽어오기
char* read_line(void);

// FILE포인터에서 개행문자 전까지 문자 읽어오기
char* read_line_f(FILE*);

// 문자열 맨 앞, 맨 뒤에서 횡공백류 제거
void trim(char*);

// 문자열 내부에 모든 횡공백류 제거
void remove_all_spaces(char*);

// 문자열내 모든 알파벳 소문자로
void to_lower(char*);
