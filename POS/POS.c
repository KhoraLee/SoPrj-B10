#include <stdio.h>
#include "type.h"
#include <locale.h>

Table tables[4]; // 테이블 4개
All_Product all_product; // 모든 상품들의 목록을 포함한 구조체

int main()
{
    setlocale(LC_ALL, "ko_KR.UTF-8"); // Force UTF-8 encoding
    printf("반가워요 World!\n");
}
