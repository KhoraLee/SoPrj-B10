// payment.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "type.h"
#include "Util.h"
#include "payment.h"

extern Table tables[4]; // 테이블 4개
extern All_Product all_product; // 모든 상품들의 목록을 포함한 구조체

// 현재 테이블의 총 주문금액을 반환
// 주문금액 0원 이하일 시 -1 반환
int table_order_price(int tablenum) {

    int i;
    int order_price = 0; // 주문액 총합 저장
    for (i = 0; i < tables[tablenum].list_size; i++) { // 현재 테이블에 주문상품 종류 수만큼 반복
        order_price += tables[tablenum].list[i].price * tables[tablenum].list[i].sales;
    }
    if (order_price <= 0) { // 주문 총액이 0 이하일 경우 -1 반환
        return -1;
    }
    return order_price;
}

// 결제 선택 메뉴 출력
void payment_choice() {
    printf("1. 한번에 결제\n");
    printf("2. 비율 결제\n");
    printf("3. 일부만 결제\n");
    printf("0. 돌아가기\n");
    printf("결제 방식 선택 - 번호 선택 > ");
    return;
}

// 한 번에 결제_메뉴 출력
void purchase_all_showmenu(int tablenum) {
    int order_price = table_order_price(tablenum);

    printf("주문 금액 확인 : %d\n", order_price);
    printf("결제하시겠습니까?\n");
    printf("1. 결제\n");
    printf("0. 돌아d가기\n");
    printf("한 번에 결제 - 번호 선택 >");
    return;
}

// 한 번에 결제_결과 출력
void purchase_all_result(int tablenum, int date) {
    printf("결제가 완료되었습니다.\n");
    printf("결제 금액 : %d\n", table_order_price(tablenum));
    printf("결제 일시 : %d\n", date);
    return;
}

// 비율 결제_메뉴 출력
// 인원수와 비율 저장할 배열를 인자로 받음
// 비율 저장할 배열은 호출할 함수에서 미리 선언
void purchase_with_ratio_showmenu(int number_of_people, int ratio_param[]) {

    // 결제 인원수가 다른 함수에서도 인자로 쓰이므로 입출력 부분 프롬프트에서 구현
    /*
    int order_price = table_order_price(tablenum);
    printf("주문 금액 확인 : %d\n", order_price;
    printf("결제할 사람 수 : ");
    scanf("%d", &number_of_people);
    */

    int i;
    int ratio[10];

    if (number_of_people < 2 || number_of_people > 10) {
        printf("오류 : 인원수는 2에서 10 사이의 정수만 가능합니다. 유효한 숫자를 입력해 주세요.\n");
        return -1;
    }
    for (i = 0; i < number_of_people;) {
        scanf("%d", &ratio[i]);
        if (ratio[i] < 1 || ratio[i] > 9) {
            printf("오류 : 비율은 1에서 9 사이의 정수입니다. 유효한 숫자를 입력해 주세요.\n");
            continue;
            // 기획서대로는 '비율 결제 메뉴를 다시 출력' 이라고 되어 있는데 확인 필요
            // 큰 문제 없다 싶으면 현재 코드대로 비율 입력만 다시 하면 되게 하기
            // 수정해야 하면 return -1; 후 프롬프트 재실행
        }
        ratio_param[i] = ratio[i]; // 인자에 저장
        i++;
    }

    printf("이대로 결제 하시겠습니까?\n");
    printf("1. 결제\n");
    printf("0. 돌아가기\n");
    printf("비율 결제 - 번호 선택 > ");

    return;
}

// 비율에 따른 개개인 결제금액 계산
// 파라미터는 (비율결제메뉴에서 받은, 결제 인원수, 테이블 번호, 계산값 저장할 인자)
// 계산값 저장할 인자는 호출할 함수에서 미리 선언
void calculate_ratio(int ratio[], int number_of_people, int tablenum, int pay_individual_param[]) {

    int pay_sum = table_order_price(tablenum); // 결제할 총액

    int i;
    int ratio_sum = 0; // 비율의 총합을 저장할 변수
    int unit; // 비율 계산시에 사용할 단위금액
    int pay_individual[10]; // 개개인 결제 할당량 저장

    for (i = 0; i < number_of_people; i++) {
        ratio_sum = ratio_sum + ratio[i]; // 입력받은 비율의 총합
    }

    unit = (pay_sum / 100) / ratio_sum * 100;
    // 비율과 곱해줄 단위금액
    // 나머지는 처음 비율 입력한 사람이 계산

    for (i = 1; i < number_of_people; i++) { // 첫 번째 사람 제외 결제금액 할당
        pay_individual[i] = unit * ratio[i]; // 단위금액 * 개개인 비율
        pay_sum -= pay_individual[i];
    }
    pay_individual[0] = pay_sum;

    // 인자에 계산값 저장
    for (i = 0; i < number_of_people; i++) {
        pay_individual_param[i] = pay_individual[i];
    }

    return;
}

// 비율 결제_결과 출력
// 파라미터는 calculate_ratio() 와 동일 + 날짜까지
void purchase_with_ratio_result(int ratio[], int number_of_people, int tablenum, int date) {

    int i;
    int pay_individual[10]; // 인원수는 10 이하
    calculate_ratio(ratio, number_of_people, tablenum, pay_individual); // 비율별 결제금액 저장

    printf("결제가 완료되었습니다.\n");
    printf("총 결제 금액 : %d\n", table_order_price(tablenum));
    for (i = 1; i <= number_of_people; i++) {
        printf("%d/%d인 결제 금액 : %d\n", i, number_of_people, pay_individual[i - 1]);
    }
    printf("결제 일시 : %d\n", date);
    return;
}


// 테이블에 있는 "전체" 상품 결제 완료 후
// 테이블 주문내역 초기화
// 전체 리스트에 결제수량 더해주기
void end_purchase(int tablenum) {

    // 전체 리스트에 결제수량 더하기
    int i, j, k;
    for (i = 0; i < tables[tablenum].list_size; i++) { // tables[tablenum].list[] 인덱스
        for (k = 0; k < all_product.list_size; k++) { // allproduct.list[] 인덱스
            for (j = 0;;) { // 상품명이 동일한지 name[] 인덱스 탐색

                // 주문시에 all_product와 같은 주문명 받아오므로 공백 검사 불필요
                // 특정 상품이 주문된 상태에서 상품 정보 변경될 시 고려 필요
                /*
                char tablename[16];
                strcpy(tablename, tables[tablenum].list[i].name);
                char allproductname[16];
                strcpy(allproductname, all_product.list[k].name);
                remove_all_spaces(tablename);
                remove_all_spaces(allproductname);
                */

                if (tables[tablenum].list[i].name[j] == all_product.list[k].name[j]) { // 첫 문자 같으면 탐색 시작
                    j++; // 다음 문자
                }
                else { // 탐색 중 다르면 다음 allproduct 인덱스 탐색
                    break;
                }
                if ((tables[tablenum].list[i].name[j] == '\0') && (all_product.list[k].name[j] == '\0')) { // 확인 완료
                    all_product.list[i].sales += tables[tablenum].list[i].sales; // 결제수량 더해주기
                    break; // 다음 allproduct 인덱스 탐색
                }
            }
        }
    }
    // 테이블 주문내역 초기화
    free(tables[tablenum].list);
    tables[tablenum].list_size = 0;

    return;
}

// 문자열을 입력받아 상품명들과 수량을 분석하여 조건에 따라
// 결제 진행후 결제된 금액 반환 또는 오류 반환
// 오류 리스트
// -1: 올바르지 않은 입력
// -2: 존재하지 않는 상품명
// -3: 올바르지 않은 수량
// -4: 주문 수량 보다 결제 수량이 더 많음
// -5: 메모리 할당 오류
int partial_pay(char* input, int table_num) {
    int parse_count = 0;
    int arr_size = 0;
    char* tmp = malloc(sizeof(char) * (strlen(input) + 1)); // 원본 문자열과 동일한 크기의 임시 배열
    char** products = NULL; // 상품명 어레이
    int* numbers = NULL; // 상품 갯수 어레이

    while (1) {
        int ret;
        size_t tmp_len;
        int number = 0; // 상품갯수
        char name[16]; // 상품명

        trim(input); // 선행 횡공백류 제거
        if (strlen(input) == 0) {
            if (!parse_count) {
                return -1; // 아무것도 입력되지 않음. 상위 프롬프트에서 체크되면 이곳에서 체크할 필요가 없음.
            } else {
                break; // 입력 분석 끝
            }
        }
        
        if (!isalpha(input[0])) return -1; // 상품 갯수 다음이 알파벳 아니면 오류 반환
        if ((ret = sscanf(input, "%[a-zA-Z ]", tmp)) != 1) break; // 상품명 읽기
        trim(tmp); // 후행 공백 제거
        if ((tmp_len = strlen(tmp)) > 15) return -1; // 실 상품명 길이가 15자가 넘으면 올마르지 않은 상품명이기에 오류 반환
        remove_all_spaces(tmp); // 띄어쓰기 제거
        to_lower(tmp); // 모두 소문자로 변환
        strcpy(name, tmp); // 상품명 임시 저장
        memcpy(input, input + tmp_len, strlen(input) - tmp_len + 1); // 숫자를 읽기 위해 상품명 부분 제거후 당기기
        parse_count++;
        
        trim(input); // 선행 횡공백류 제거
        if (!isdigit(input[0])) return -1; // 상품명 다음이 숫자가 아니면 오류 반환
        if ((ret = sscanf(input, "%[0-9.]", tmp)) != 1) break; // 상품 갯수 읽기
        if (strstr(tmp, ".") != NULL) return -3; // 상품 갯수에 소수점이 포함됨 포함시 에러 반환 TODO: 1.0, 1.00등은 허용할지? <- 기획서 수정필요?
        
        number = atoi(tmp); // 상품 갯수 임시 저장
        if (number < 1) return -3; // 1보다 작은 숫자임
        tmp_len = strlen(tmp); // 상품갯수 길이
        memcpy(input, input + tmp_len, strlen(input) - tmp_len + 1); // 숫자를 읽기 위해 상품명 부분 제거후 당기기
        parse_count++;
        
        // 임시 배열에 추출한 상품명과 갯수 기록
        void* realloced_products = realloc(products, sizeof(char*) * ++arr_size);
        void* realloced_numbers = realloc(numbers, sizeof(int) * arr_size);
        void* malloced_name = malloc(sizeof(char) * 16);
        // malloc, realloc에 실패하면
        if (!realloced_products || !realloced_numbers || !malloced_name) {
            // 이전에 할당된 메모리 free
            if (!realloced_products) free(products);
            if (!realloced_numbers) free(numbers);
            return -5; // 오류 반환
        }
        
        // realloc된 메모리 주소 할당
        products = realloced_products;
        numbers = realloced_numbers;
        strcpy(malloced_name, name); // 문자열 복사
        
        // 어레이에 저장
        int index = arr_size - 1;
        products[index] = malloced_name;
        numbers[index] = number;
    }

    if (parse_count % 2 != 0) return -1; // 상품명과 상품 갯수가 짝이 맞지 않음 -> 입력이 잘못됨

    // 주문 내역에 결제할 상품이 있는지 확인후 인덱스 저장
    int* index_table = malloc(sizeof(int) * arr_size);
    for (int i = 0; i < arr_size; i++) {
        int index = -1;
        for (int j = 0; j < tables[table_num].list_size; j++) {
            char tmp[16];
            strcpy(tmp, tables[table_num].list[j].name);
            remove_all_spaces(tmp);
            to_lower(tmp);
            if (strcmp(tmp, products[i]) == 0) {
                index = j;
                break;
            }
        }
        if (index == -1) return -2; // 존재하지 않는 상품명
        if (tables[table_num].list[index].sales < numbers[i]) return -4; // 주문한 상품수보다 계산하려는 상품수가 더 많음
        index_table[i] = index; // 인덱스 저장
    }

    // 정말로 결제?
    printf("이대로 결제하시겠습니까?\n");
    printf("1. 결제\n");
    printf("0. 돌아가기\n");
    printf("POS / 일부만 결제 - 번호 선택 > ");
    
    char* confirm_str = read_line(); // 선택지 입력받기
    
    while(1) {
        trim(confirm_str);
        to_lower(confirm_str);
        if (!strcmp(confirm_str, "0") || !strcmp(confirm_str, "back")) return -10; // 돌아가기
        else if (!strcmp(confirm_str, "1") || !strcmp(confirm_str, "one")) break; // 결제 진행

        // 입력 오류, 다시 입력받기
        printf("오류 : 0(back) 또는 1(one)만 입력하십시오.\n");
        printf("POS / 일부만 결제 - 번호 선택 > ");
        free(confirm_str); // 기존 문자열 free
        confirm_str = read_line(); // 재입력 받기
    }

    int total_price = 0; // 결제하려는 토탈 금액

    for (int i = 0; i < arr_size; i++) {
        int index = index_table[i];
        tables[table_num].list[index].sales -= numbers[i]; // 테이블에 존제하는 갯수 감소

        int ap_index = -1;
        for (int j = 0; j < all_product.list_size; j++) {
            if (strcmp(all_product.list[j].name, tables[table_num].list[index].name) == 0) {
                ap_index = j;
                break;
            }
        }
        all_product.list[ap_index].sales += numbers[i]; // 정산을 위해 판매 내역에 더하기
        total_price += numbers[i] * all_product.list[ap_index].price;
    }
    
    // 작업이 끝났으니 malloc 한 항목들 free
    free(tmp);
    free(numbers);
    free(index_table);
    for (int i = 0; i < arr_size; i++) {
        free(products[i]);
    }
    free(products);
    
    return total_price;
}
