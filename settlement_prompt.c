//
//  settlement_prompt.c
//  POS
//
//  Created by 정준규 on 2023/04/25.
//

#include "settlement_prompt.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void settlement_prompt() {
    while (1) {
        printf("1. 정산파일을 보시겠습니까?\n");
        printf("0. 돌아가기\n");

        char* input = read_line(); // 선택지 입력받기
        trim(input);
        to_lower(input);

        if (!strcmp(input, "1") || !strcmp(input, "one")) {
            printf("날짜별 정산 내역 - 날짜입력 > ");
            char* date_input = read_line();
            trim(date_input);
            to_lower(date_input);
            print_settlement(date_input);
        }
        else if (!strcmp(input, "0") || !strcmp(input, "back")) {
            return;
        }
        else {
            int cmd_int;
            if (strlen(input) == 0) {
                printf("오류 : 명령어를 입력해주세요.\n");
            }
            else if (is_contain_spaces(input)) {
                printf("오류 : 명령어가 너무 많습니다. 최대 1개의 명령어만 인자로 입력해주세요.\n");
            }
            else if ((cmd_int = is_correct_command(input)) != -1) {
                printf("오류 : 현재 메뉴에 '%d'번 선택지는 존재하지 않습니다.", cmd_int);
            }
            else {
                printf("오류 : '%s'이라는 명령어는 없습니다\n", input);
            }
            printf("-----------------+-------------------------------------+----------------------------------");
            // TODO: 올바른 입력 출력
            printf("-----------------+-------------------------------------+----------------------------------");
        }
    }
}
