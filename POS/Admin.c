#include "Admin.h"
#include "type.h"
#include "Util.h"
#include <stdio.h>
extern Table tables[4]; // 테이블 4개
extern All_Product all_product; // 모든 상품들의 목록을 포함한 구조체
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

void PrintReceipt(int t) //주문내역출력
{
	printf("  <주문 내역>\n");
	printf("    테이블 번호 : %d번\n", t);
	printf("    주문 내역 : \n");
	//내역
	int  sum = 0;
	for (int i = 0; i < tables[t].list_size; i++)
	{
		sum += (tables[t].list[i].price * tables[t].list[i].sales );
		printf("    %d.   %s %d %d\n", i + 1, tables[t].list[i].name, tables[t].list[i].price, tables[t].list[i].sales);
	}
	printf("    합계 : %d원\n",sum);
	// printf("POS / %d번 테이블 - 주문 내역 출력 >", t); //이후 명령어 입력받아야함
	// 마지막 프린트문은 Cancle함수에 PrintReceipt 사용하기 위해 주석처리
	// 메인에서 printf하면 될듯
}
//상품 주문 명령어 (2번) 을 입력하면 Menu부터 호출한 후 상품명 입력받음 ->Order 호출
void Menu(int t)
{
	printf("  <상품 주문>\n");
	printf("    테이블 번호 : %d번\n", t);
	printf("    상품 목록 : \n");
	for (int i = 0; i < all_product.list_size; i++)
		printf("    %d.   %s\n", i + 1, all_product.list[i].name);
	printf("POS / (상품 주문) - 상품명 입력 >");

}
int Order(int t, char* string)//상품 주문
{
	if (all_product.list_size == 0) //product.txt가 null일 때
	{
		printf("오류 : 'product.txt'가 비어있습니다. 상품 추가를 먼저 해주세요\n");
		return -1;
	}
	else {
		remove_all_spaces(string); // string 을 입력받고, 공백을 다 없애줌

		for (int i = 0; i < all_product.list_size; i++)
		{
			if (!strcmp(string, all_product.list[i].name))//메뉴에 상품명이 있으면
			{
				int flag = 0; //테이블 내에 상품이 있는지 확인 .. 있으면 1, 없으면 0

				for (int j = 0; j < tables[t].list_size; j++)
				{
					if (!strcmp(string, tables[t].list[j].name)) // 테이블 내에 상품이 이미 있음
					{	//한개 시켰다가 취소해서 0인경우 ?  ... 상관없음
						flag = 1;
						tables[t].list[j].sales++; //주문한 상품의 개수 +1
						break;
					}
				}
				if (!flag) // 테이블 내에 상품이 없음 , malloc 으로 배열 할당 후 추가 주문마다 realloc
				{
					if (tables[t].list_size == 0) {  //주문내역이 아예 비어있음
						tables[t].list = (Product*)malloc(sizeof(Product));
						strcpy(tables[t].list[tables[t].list_size].name, string); //상품명 저장
						tables[t].list[tables[t].list_size].price = all_product.list[i].price; //가격 저장
						tables[t].list[tables[t].list_size].sales = 1; //개수 저장
						tables[t].list_size++; //다음 인덱스를 가리킴
					}
					else {
						tables[t].list = realloc(tables[t].list, ((tables[t].list_size + 1) * (sizeof(Product))));
						strcpy(tables[t].list[tables[t].list_size].name, string); //상품명 저장
						tables[t].list[tables[t].list_size].price = all_product.list[i].price; //가격 저장
						tables[t].list[tables[t].list_size].sales = 1; //개수 저장
						tables[t].list_size++;
					}

				}
				return 1;
			}
			else {//메뉴에 상품명이 없으면
				//오류 출력 및 올바른 입력방법에 대한 안내출력
				printf("오류 : 상품목록에 없는 상품명입니다. 상품목록에 있는 상품명을 입력해주세요\n");
				return -1;
			}
		}
	}
	

	
}
//상품 주문 명령어 (3번) 을 입력하면 주문내역부터 호출한 후 상품명 입력받음 -> Cancle 호출
void Cancle(int t, char* string)//상품 취소
{
	if (all_product.list_size == 0) //product.txt가 null일 때
	{
		printf("오류 : 'product.txt'가 비어있습니다. 상품 추가를 먼저 해주세요\n");
		return -1;
	}
	else {
		remove_all_spaces(string); // string 을 입력받고, 공백을 다 없애줌

		int flag = 0; //테이블 내에 상품이 있는지 확인 .. 있으면 1, 없으면 0
		for (int j = 0; j < tables[t].list_size; j++)
		{
			if (!strcmp(string, tables[t].list[j].name)) // 주문내역에 상품이 이미 있음
			{	// 취소해서 0인경우 , 테이블 주문내역에 sales : 0 이라고 표시되고 
				//이름이 지워지지 않으므로  이 경우도 따져야함 (1. 그냥 리턴하기(성공했다고 침), 2. 메세지 출력하고 기획서고치기)
				//둘중 하나 택
				if (tables[t].list[j].sales == 0)
				{
					return 1; //성공했다고 침
					//printf("오류 : 주문내역에 없는 상품명입니다. 주문내역에 있는 상품명을 입력해주세요\n"); 
				}
				else {
					flag = 1;
					tables[t].list[j].sales--; //주문한 상품의 개수 -1
					return 1;
				}

			}
			else { //주문내역에 상품명이 없으면
				   //오류 출력 및 올바른 입력방법에 대한 안내출력
				printf("오류 : 주문내역에 없는 상품명입니다. 주문내역에 있는 상품명을 입력해주세요\n");
				return -1;
			}
		}	
	}
}