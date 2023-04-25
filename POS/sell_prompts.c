//
//  sell.c
//  POS
//
//  Created by 이승윤 on 2023/04/24.
//

#include "sell_prompts.h"
#include "payment_prompts.h"
#include "types.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>

extern Table tables[4]; // 테이블
extern Product_Array all_products;

void sell_prompt() {
    int table_num = -1;

    while (1) {
        printf("<테이블 리스트>\n");
        printf("\t1. 1번 테이블\n");
        printf("\t2. 2번 테이블\n");
        printf("\t3. 3번 테이블\n");
        printf("\t4. 4번 테이블\n");
        printf("\t0. 돌아가기\n");

        printf("POS / 판매관리(테이블 관리) - 테이블 번호 선택 > ");
        char* input = read_line(); // 선택지 입력받기
        trim(input);
        to_lower(input);
        if (!strcmp(input, "1") || !strcmp(input, "one")) {
            table_num = 1;
        } else if (!strcmp(input, "2") || !strcmp(input, "two")) {
            table_num = 2;
        } else if (!strcmp(input, "3") || !strcmp(input, "three")) {
            table_num = 3;
        } else if (!strcmp(input, "4") || !strcmp(input, "four")) {
            table_num = 4;
        } else if (!strcmp(input, "0") || !strcmp(input, "back")) {
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
                printf("오류 : '%s'이라는 명령어는 없습니다\n", input);
            }
            printf("-----------------+-------------------------------------+----------------------------------\n");
            // TODO: 올바른 입력 출력
            printf("-----------------+-------------------------------------+----------------------------------\n");
        }
        free(input); // 입력받은 문자열 free
        if (table_num > 0) {
            table_management_prompt(table_num);
        }
    }
}

void table_management_prompt(int table_num) {
    while(1) {
        printf("<%d번 테이블>\n", table_num);
        printf("\t1. 주문내역 출력\n");
        printf("\t2. 상품 주문\n");
        printf("\t3. 상품 취소\n");
        printf("\t4. 결제\n");
        printf("\t0. 돌아가기\n");

        printf("POS / %d번 테이블 - 테이블 번호 선택 > ", table_num);
        char* input = read_line(); // 선택지 입력받기
        trim(input);
        to_lower(input);
        if (!strcmp(input, "1") || !strcmp(input, "one")) {
            if (is_empty_table(table_num)) {
                printf("오류 : 주문된 상품이 없습니다.\n");
            } else {
                print_receipt(table_num);
            }
        } else if (!strcmp(input, "2") || !strcmp(input, "two")) {
            order_product(table_num);
        } else if (!strcmp(input, "3") || !strcmp(input, "three")) {
            if (is_empty_table(table_num)) {
                printf("오류 : 주문된 상품이 없습니다.\n");
            } else {
                cancel_order(table_num);
            }
        } else if (!strcmp(input, "4") || !strcmp(input, "four")) {
            if (is_empty_table(table_num)) {
                printf("오류 : 주문된 상품이 없습니다.\n");
            } else {
                process_payment(table_num);
            }
        } else if (!strcmp(input, "0") || !strcmp(input, "back")) {
            return;
        } else {
            int cmd_int;
            if (strlen(input) == 0) {
                printf("오류 : 명령어를 입력해주세요.\n");
            } else if (is_contain_spaces(input)) {
                printf("오류 : 명령어가 너무 많습니다. 최대 1개의 명령어만 인자로 입력해주세요.\n");
            } else if ((cmd_int = is_correct_command(input)) != -1) {
                printf("오류 : 현재 메뉴에 '%d'번 선택지는 존재하지 않습니다.\n", cmd_int);
            } else {
                printf("오류 : ‘%s’이라는 명령어는 없습니다\n", input);
            }
            printf("-----------------+-------------------------------------+----------------------------------\n");
            // TODO: 올바른 입력 출력
            printf("-----------------+-------------------------------------+----------------------------------\n");
        }
        free(input); // 입력받은 문자열 free
    }
}

// 주문내역출력
void print_receipt(int table_num) {
    Table *table = &tables[table_num - 1];
    int total_price = 0;
    
    printf("<주문 내역>\n");
    printf("\t테이블 번호 : %d번\n", table_num);
    printf("\t주문 내역 : \n");
    
    // 주문 내역 출력
    for (int i = 0; i < table->length; i++) {
        if (table->products[i].amount == 0) continue;
        printf("%s\t%d\t%d\n", table->products[i].name, table->products[i].price, table->products[i].amount);
        total_price += table->products[i].price * table->products[i].amount;
    }
    // 합계 금액 출력
    printf("\t합계 : %d원\n", total_price);
}

void order_product(int table_num) {
    int i;
    Product *product_to_order = NULL;
    
    while(1) {
        printf("<상품 주문>\n");
        printf("\t1. 상품명 입력\n");
        printf("\t0. 돌아가기\n");
        printf("POS / (상품 주문) - 번호 선택 > ");
        char* confirm_str = read_line(); // 선택지 입력받기

        trim(confirm_str);
        to_lower(confirm_str);
        if (!strcmp(confirm_str, "0") || !strcmp(confirm_str, "back")) {
            free(confirm_str); // 기존 문자열 free
            return; // 돌아가기
        } else if (!strcmp(confirm_str, "1") || !strcmp(confirm_str, "one")){
            free(confirm_str); // 기존 문자열 free
            break; // 결제 진행
        }
        // 입력 오류, 다시 입력받기
        printf("오류 : 0(back) 또는 1(one)만 입력하십시오.\n");
        free(confirm_str); // 기존 문자열 free
    }
    
    printf("<상품 주문>");
    printf("\t테이블 번호 %d번\n", table_num);
    printf("\t상품 목록:\n");
    for (i = 0; i < all_products.length; i++)
    {
        printf("%d. %s\t%d\n", i + 1, all_products.products[i].name, all_products.products[i].price);
    }

    // 입력받기
    while (1) {
        printf("POS /(상품 주문) - 상품명 입력 > ");
        char *input = read_line();
        trim(input);
        remove_all_space(input);
        to_lower(input);
        for (i = 0; i < all_products.length; i++) {
            char comparing[16];
            strcpy(comparing, all_products.products[i].name);
            remove_all_space(comparing);
            to_lower(comparing);
            if (strcmp(input, comparing) == 0) {
                product_to_order = &all_products.products[i];
            }
        }

        if (product_to_order != NULL) {
            break;
        }

        printf("오류 : 상품목록에 없는 상품명입니다. 상품목록에 있는 상품명을 입력해주세요\n");
    }
    
    while(1) {
        printf("정말로 주문하시겠습니까?\n");
        printf("1. 주문\n");
        printf("0. 돌아가기\n");
        printf("POS / 일부만 결제 - 번호 선택 > ");
        
        char* confirm_str = read_line(); // 선택지 입력받기

        trim(confirm_str);
        to_lower(confirm_str);
        if (!strcmp(confirm_str, "0") || !strcmp(confirm_str, "back")) {
            free(confirm_str); // 기존 문자열 free
            return; // 돌아가기
        } else if (!strcmp(confirm_str, "1") || !strcmp(confirm_str, "one")) {
            free(confirm_str); // 기존 문자열 free
            break; // 주문 진행
        }
        // 입력 오류, 다시 입력받기
        printf("오류 : 0(back) 또는 1(one)만 입력하십시오.\n");
        free(confirm_str); // 기존 문자열 free
    }

    // 주문목록에 추가
    add_order(table_num, product_to_order);
}

void add_order(int table_num, Product *order_product) {
    Table *table = &tables[table_num - 1];
    int is_already_existing_order = 0; //테이블 내에 상품이 있는지 확인 .. 있으면 1, 없으면 0
    
    for (int j = 0; j < table->length; j++) {
        char tname[16];
        strcpy(tname, table->products[j].name);
        if (!strcmp(order_product->name, tname)) // 테이블 내에 상품이 이미 있음
        {    //한개 시켰다가 취소해서 0인경우 ?  ... 상관없음
            is_already_existing_order = 1;
            table->products[j].amount++; //주문한 상품의 개수 +1
            break;
        }
    }
    if (!is_already_existing_order) {
        if (table->length == 0) {  //주문내역이 아예 비어있음
            if ((table->products = malloc(sizeof(Product))) == NULL) { //메모리 부족으로 malloc 호출 실패하면 종료됨
                printf("오류 : 메모리 문제로 주문에 실패하였습니다. 이전 메뉴로 돌아갑니다.\n");
                return;
            }
            strcpy(table->products[0].name, order_product->name); //상품명 저장
            table->products[0].price = order_product->price; //가격 저장
            table->products[0].amount = 1; //개수 저장
            table->length++; //다음 인덱스를 가리킴
        } else {
            void* realloced = realloc(table->products, (table->length + 1) * sizeof(Product));
            if (realloced == NULL) {
                printf("오류 : 메모리 문제로 주문에 실패하였습니다. 이전 메뉴로 돌아갑니다.\n");
                return;
            } else {
                table->products = realloced;
            }
            strcpy(table->products[table->length].name, order_product->name); //상품명 저장
            table->products[table->length].price = order_product->price; //가격 저장
            table->products[table->length].amount = 1; //개수 저장
            table->length++;
        }
    }
}

void cancel_order(int table_num) {
    Table *table = &tables[table_num - 1];
    int is_existing_order = 0;
    
    while(1) {
        printf("상품 취소하기");
        printf("취소하시겠습니까?\n");
        printf("1. 상품 취소\n");
        printf("0. 돌아가기\n");
        printf("POS / (상품 취소) - 번호 선택 > ");
        char* confirm_str = read_line(); // 선택지 입력받기

        trim(confirm_str);
        to_lower(confirm_str);
        if (!strcmp(confirm_str, "0") || !strcmp(confirm_str, "back")) {
            free(confirm_str); // 기존 문자열 free
            return; // 돌아가기
        } else if (!strcmp(confirm_str, "1") || !strcmp(confirm_str, "one")){
            free(confirm_str); // 기존 문자열 free
            break; // 결제 진행
        }
        // 입력 오류, 다시 입력받기
        printf("오류 : 0(back) 또는 1(one)만 입력하십시오.\n");
        free(confirm_str); // 기존 문자열 free
    }
    
    print_receipt(table_num);

    int idx = -1;
    while (1) {
        printf("POS / (상품 취소) - 상품명 입력 > ");
        char *input = read_line();
        trim(input);
        remove_all_space(input); // string 을 입력받고, 공백을 다 없애줌
        
        for (int i = 0; i < table->length; i++) {
            char comparing[16];
            strcpy(comparing, table->products[i].name);
            remove_all_space(comparing);
            to_lower(comparing);
            if (!strcmp(input, comparing)) { // 주문내역에 상품이 이미 있음
                 if (table->products[i].amount == 0) {
                     printf("오류 : 주문내역에 없는 상품명입니다. 주문내역에 있는 상품명을 입력해주세요\n");
                 } else {
                     idx = i;
                     is_existing_order = 1;
                     break;
                 }
             }
        }

        if (!is_existing_order) {
            printf("오류 : 주문내역에 없는 상품명입니다. 주문내역에 있는 상품명을 입력해주세요\n");
        } else {
            break;
        }
    }
    
    while(1) {
        printf("정말로 취소하시겠습니까?\n");
        printf("1. 취소\n");
        printf("0. 돌아가기\n");
        printf("POS / (상품 취소) - 번호 선택 > ");
        
        char* confirm_str = read_line(); // 선택지 입력받기

        trim(confirm_str);
        to_lower(confirm_str);
        if (!strcmp(confirm_str, "0") || !strcmp(confirm_str, "back")) {
            free(confirm_str); // 기존 문자열 free
            return; // 돌아가기
        } else if (!strcmp(confirm_str, "1") || !strcmp(confirm_str, "one")) {
            free(confirm_str); // 기존 문자열 free
            break; // 취소 진행
        }
        // 입력 오류, 다시 입력받기
        printf("오류 : 0(back) 또는 1(one)만 입력하십시오.\n");
        free(confirm_str); // 기존 문자열 free
    }
    
    table->products[idx].amount--; //주문한 상품의 개수 -1
}

int is_empty_table(int table_num) {
    Table *table = &tables[table_num - 1];
    int total_order = 0;
    for (int i = 0; i < table->length; i++) {
        total_order += table->products[i].amount;
    }
    if (total_order == 0) {
        return 1;
    } else {
        return 0;
    }
}
