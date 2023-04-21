#pragma once

// 현재 테이블의 총 주문금액을 반환
int table_order_price(int);

// 결제 선택 메뉴 출력
void payment_choice();

// 한 번에 결제_메뉴 출력
void purchase_all_showmenu(int);

// 한 번에 결제_결과 출력
void purchase_all_result(int, int);

// 비율 결제_메뉴 출력
void purchase_with_ratio_showmenu(int, int []);

// 입력받은 비율에 따른 개개인 결제금액 계산
void calculate_ratio(int [], int, int, int []);

// 비율 결제_결과 출력
void purchase_with_ratio_result(int [], int, int, int);

// 테이블 내 "전체" 상품 결제 완료 후
// 전역 allproduct 결제수량 더해주고 테이블 주문내역 초기화
void end_purchase(int);

int partial_pay(char*, int);
