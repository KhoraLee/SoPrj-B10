
#pragma once
void ShowTableMenu(int t);
//1.주문내역출력 2. 상품 주문 3. 상품 취소
//4. 결제    0. 돌아가기
//인자 : table 번호

void PrintReceipt(int t);
//주문내역 출력 , 인자 : table 번호


void Order(char* string); //상품 주문
void Cancle(char* string); //상품 취소