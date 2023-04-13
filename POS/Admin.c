#include "Admin.h"
#include "type.h"
#include "Util.h"
#include <stdio.h>

void ShowTableMenu(int t)
{
	printf("<%d번 테이블>\n", t);
	printf("    1.  주문내역 출력\n");
	printf("    2.  상품 주문\n");
	printf("    3.  상품 취소\n");
	printf("    4.  결제\n");
	printf("    0.  돌아가기\n");
	printf("%d번 테이블 - 번호 선택 >", t); //이후 명령어 입력받아야함
}

void PrintReceipt(int t)
{
	printf("  <주문 내역>\n");
	printf("    테이블 번호 : %d번\n", t);
	printf("    주문 내역: \n");
	//내역
	printf("    합계 : 원\n");
	printf("%d번 테이블 - 주문 내역 출력 >", t); //이후 명령어 입력받아야함

}

void Order(char* string)
{
	remove_all_spaces(string); // string 을 입력받고, 공백을 다 없애줌
	//printf("%s", string);
	//동치비교


	
}//상품 주문
void Cancle(char* string)
{

}//상품 취소
