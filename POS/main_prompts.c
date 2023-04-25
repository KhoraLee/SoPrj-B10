#include "main_prompts.h"
#include "sell_prompts.h"
#include "utils.h"
#include "product.h"
#include "settlement.h"

#include <stdlib.h>
#include <string.h>

extern Table tables[4]; // 테이블 4개
extern Product_Array all_products; // 모든 상품들의 목록을 포함한 구조체
extern int date;

void main_prompt() {
    while (1) {
        printf("<메인 메뉴>\n");
        printf("\t1. 판매 관리\n");
        printf("\t2. 날짜별 정산\n");
        printf("\t3. 새 상품 추가\n");
        printf("\t4. 종료\n");

        printf("POS / 메인 메뉴 - 번호 선택 > ");
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
            if (exit_check() == 0) {
                write_product_file();
                save_settlement();
                return;
            } else {
                printf("오류 : 모든 테이블에 결제가 끝나지 않아 종료가 불가능합니다.\n");
            }
        } else {
            int cmd_int;
            if (strlen(input) == 0) {
                printf("오류 : 명령어를 입력해주세요.\n");
            } else if (is_contain_spaces(input)) {
                printf("오류 : 명령어가 너무 많습니다. 최대 1개의 명령어만 인자로 입력해주세요.\n");
            } else if ((cmd_int = is_correct_command(input)) != -1) {
                printf("오류 : 현재 메뉴에 '%d'번 선택지는 존재하지 않습니다.\n", cmd_int);
            } else {
                printf("오류 : '%s'이라는 명령어는 없습니다\n", input);
            }
            printf("-----------------+-------------------------------------+----------------------------------");
            // TODO: 올바른 입력 출력
            printf("-----------------+-------------------------------------+----------------------------------");
        }
        free(input); // 입력받은 문자열 free
    }
}

int exit_check() {
    for (int i = 0; i < 4; i++) {
        Table *table = &tables[i];
        for (int j = 0; j < table->length; j++) {
            if (table->products[j].amount != 0) {
                return -1;
            }
        }
    }
    return 0;
}
