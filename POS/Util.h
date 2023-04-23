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

// 문자가 알파벳인지 체크
// isalpha가 있지만 윈도우 환경에서 한글이 들어가면 뻗어버리는 문제가 있음.
int is_alpha(int);

// 문자열내 모든 알파벳 소문자로
void to_lower(char*);
