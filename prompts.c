//
//  prompts.c
//  POS
//
//  Created by 이승윤 on 2023/04/24.
//
#include "sell_prompts.h"
#include "utils.h"
#include "prompts.h"

#include <stdlib.h>
#include <string.h>

extern int date;

void main_prompt() {
    while (1) {
        printf("<메인 메뉴>\n");
        printf("\t1. 판매 관리\n");
        printf("\t2. 날짜별 정산\n");
        printf("\t3. 새 상품 추가\n");
        printf("\t4. 종료\n");

        printf("POS / 메인 메뉴 – 번호 선택 > ");
        char* input = read_line(); // 선택지 입력받기
        trim(input);
        to_lower(input);
        if (!strcmp(input, "1") || !strcmp(input, "one")) {
            sell_prompt();
        } else if (!strcmp(input, "2") || !strcmp(input, "two")) {
            settlement_prompt();
        } else if (!strcmp(input, "3") || !strcmp(input, "three")) {
            add_product_prompt();
        } else if (!strcmp(input, "4") || !strcmp(input, "four")) {
            // TODO: 종료 가능인지 체크 후 종료
            return;
        } else {
            int cmd_int;
            if (strlen(input) == 0) {
                printf("오류 : 명령어를 입력해주세요.\n");
            } else if (is_contain_spaces(input)) {
                printf("오류 : 명령어가 너무 많습니다. 최대 1개의 명령어만 인자로 입력해주세요.\n");
            } else if ((cmd_int = is_correct_command(input)) != -1) {
                printf("오류 : 현재 메뉴에 '%d'번 선택지는 존재하지 않습니다.", cmd_int);
            } else {
                printf("오류 : ‘6’이라는 명령어는 없습니다\n");
            }
            printf("-----------------+-------------------------------------+----------------------------------");
            // TODO: 올바른 입력 출력
            printf("-----------------+-------------------------------------+----------------------------------");
        }
        free(input); // 입력받은 문자열 free
    }
}

