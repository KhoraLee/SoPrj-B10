#include "add_product_prompts.h"
#include "types.h"
#include "product.h"
#include "utils.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

extern Product_Array all_products; // 모든 상품들의 목록을 포함한 구조체

void add_product_prompt() {
    while (1) {
        printf("<상품 추가>\n");
        printf("\t1. 상품명 입력\n");
        printf("\t0. 돌아가기\n");
        
        printf("POS / 새 상품 추가 - 번호 선택 > ");
        char* input = read_line(); // 선택지 입력받기
        trim(input);
        to_lower(input);
        if (!strcmp(input, "1") || !strcmp(input, "one")) {
            if(add_product_prompt2()==0){
                return;
            }
        }
        else if (!strcmp(input, "0") || !strcmp(input, "back")) {
            return;
        }
        else {
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
            printf("-----------------+-------------------------------------+----------------------------------\n");
            // TODO: 올바른 입력 출력
            printf("-----------------+-------------------------------------+----------------------------------\n");
        }
    }
}

    
int add_product_prompt2(){
    char name[16];
    int price;
    int idx;
    
    while(1){
        while(1){
            printf("POS / 새 상품 추가 - 상품명 입력 > ");
            if(read_name(name)){
                if ((idx = productcmp(name)) >= 0) { //product_cmp로 동치비교를 해서 동치인 인덱스 반환
                    if (all_products.products[idx].amount > 0) {
                        printf("오류 : 오늘 이미 판매된적 있는 상품입니다. 상품정보를 변경할 수 없습니다.\n");
                        return 0;
                    }
                }
                break;
            }else{
                while(getc(stdin) != '\n')
                    ;
            }
        }
        
        while(1){
            printf("POS / 새 상품 추가 - 상품가격 입력 > ");
            if(read_price(&price)){
                break;
            }else{
                while(getc(stdin) != '\n')
                    ;
            }
        }
        
        while(1){
            printf("POS / 새 상품 추가\n");
            printf("\t상품명: %s\n", name);
            printf("\t상품가격: %d\n", price);
            printf("\t1. 저장하기\n");
            printf("\t0. 돌아가기\n");
            printf("\t저장하시겠습니까? > ");
            char* input = read_line();
            trim(input);
            to_lower(input);
            if (!strcmp(input, "1") || !strcmp(input, "one")) {
                add_product(name, price);
                break;
            }
            else if (!strcmp(input, "0") || !strcmp(input, "back")) {
                return 0;
            }
            else {
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
                printf("-----------------+-------------------------------------+----------------------------------\n");
                // TODO: 올바른 입력 출력
                printf("-----------------+-------------------------------------+----------------------------------\n");
            }
        }
        
        while(1){
            printf("POS / 새 상품 추가\n");
            printf("\t1. 계속 추가하기\n");
            printf("\t0. 돌아가기\n");
            printf("계속 추가하시겠습니까? > ");
            
            char* input = read_line();
            trim(input);
            to_lower(input);
            if (!strcmp(input, "1") || !strcmp(input, "one")) {
                add_product(name, price);
                break;
            }
            else if (!strcmp(input, "0") || !strcmp(input, "back")) {
                return 0;
            }
            else {
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
                printf("-----------------+-------------------------------------+----------------------------------\n");
                // TODO: 올바른 입력 출력
                printf("-----------------+-------------------------------------+----------------------------------\n");
            }
        }
    }
}
    
int read_name(char* np) {
    char c;
    int length;
    while ((c = getc(stdin)) == ' ' || c == '\t') //횡공백류열 제거
        ;
        
    if (c == '\n') //횡공백류열만 입력한 라인
        return 0;
    if (!is_alpha(c)) { //상품명에 알파벳이 아닌 글자 포함
        printf("오류 : 상품명에 알파벳이 아닌 것이 포함되어 있습니다. 상품명은 알파벳으로만 입력할 수 있습니다.\n");
        // \n까지 읽어야
        return 0;
    }
    ungetc(c, stdin);
        
    for (length = 0; length < 16; length++) { //최대 15글자까지 읽음
        c = getc(stdin);
        if (c == '\n') {
            return 1;
        }
        if (c == '\t') {
            break;
        }
        if (is_alpha(c) || c == ' ') { // 상품명은 알파벳 or 표준공백
            *(np + length) = c;
        }
        else { //위의 둘이 아니라면 에러
            printf("오류 : 상품명에 알파벳이 아닌 것이 포함되어 있습니다. 상품명은 알파벳으로만 입력할 수 있습니다.\n");
            return 0;
        }
    }
        
    if (length == 16) // 길이가 16이 되었는데
        if (is_alpha(c)) {
            printf("오류 : 상품명 길이가 15글자를 초과했습니다. 상품명은 1~15글자의 알파벳 및 표준공백(스페이스바)으로만 설정할 수 있습니다.\n");
            return 0;
        }
        
    for (; *(np + length - 1) == ' '; length--)
        ;//상품명 뒤에오는 표준공백 삭제
    *(np + length) = '\0';
        
    while ((c = getc(stdin)) == ' ' || c == '\t')//횡공백류열 제거
        ;
        
    if (c != '\n') {
        printf("오류 : 상품명은 다음과 같은 형식으로 입력할 수 있습니다. <횡공백류열0><상품명><횡공백류열0>\n");
        return 0;            //에러
    }
    else {
        return 1;
    }
}


int read_price(int* pp) {
    char c;
    int length, price = 0;


    while ((c = getc(stdin)) == ' ' || c == '\t')//횡공백류열 제거
        ;
    if (!isdigit(c)) {//상품가격이 숫자가 아니면 에러
        printf("오류 : 상품가격에 숫자가 아닌 것이 포함되어 있습니다. 상품가격은 숫자로만 입력할 수 있습니다.\n");
        return 0;
    }
    if (c == '0') {//첫글자가 0이면 에러
        printf("오류 : 상품가격의 첫글자가 0입니다. 상품 가격은 0으로 시작할 수 없습니다.\n");
        return 0;
    }
    ungetc(c, stdin);

    for (length = 0; length < 7; length++) {
        c = getc(stdin);
        if (isdigit(c)) { // 상품가격은 숫자
            price *= 10;
            price += c - '0';
        }
        else
            break;
    }
    if (length == 7) { // 길이가 8이 되었는데
        if (isdigit(c)) {//마지막 문자가 숫자이면 길이 초과
            printf("오류 : 상품가격이 100만원 이상입니다. 상품가격은 100만원보다 작게 정해야합니다.\n");
            return 0;
        }
    }
    if (c != ' ' && c != '\t' && c != '\n') {
        printf("오류 : 상품가격에 숫자가 아닌 것이 포함되어 있습니다. 상품가격은 숫자로만 입력할 수 있습니다.\n");
        return 0;//상품가격 읽다가 위 두 조건 아니고 빠져나오면 에러
    }
    ungetc(c,stdin);

    while ((c = getc(stdin)) == ' ' || c == '\t')//공백류열 흡수
        ;
    
//    if (price % 100) {//10원 없어요
//        printf("오류 : 상품가격은 100으로 나누었을 때 나머지가 0이 아닙니다. 상품가격은 100단위로 정해야합니다.\n");
//        return 0;
//    }
    
    if (c != '\n') {// 딴게 나와??
        printf("오류 : 상품가격은 다음과 같은 형식으로 입력할 수 있습니다. <횡공백류열0><상품가격><횡공백류열0>\n");
        return 0;            //에러
    }
    else if(price % 100){
        printf("오류 : 상품가격은 100으로 나누었을 때 나머지가 0이 아닙니다. 상품가격은 100단위로 정해야합니다.\n");
        return 0;
    } {
        *pp = price;
        return 1;
    }
}
