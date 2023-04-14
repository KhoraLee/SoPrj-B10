#pragma once

// 현재 테이블의 총 주문금액을 반환
int table_order_price(int tablenum);

// 결제 선택 메뉴 출력
void payment_choice();

// 한 번에 결제_메뉴 출력
void purchase_all_showmenu(int tablenum);

// 한 번에 결제_결과 출력
void purchase_all_result(int tablenum, int date);

// 비율 결제_메뉴 출력
int purchase_ratio_showmenu(int tablenum);

// 입력받은 비율에 따른 개개인의 결제금액 계산하는 함수
int calculate_ratio(int ratio[], int people_num, int tablenum);

// 비율 결제_결과 출력
void purchase_ratio_result(int ratio[], int people_num, int tablenum, int date);
