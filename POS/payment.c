// payment.c
#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "payment.h"

extern Table tables[4]; // 테이블 4개
extern All_Product all_product; // 모든 상품들의 목록을 포함한 구조체

// 현재 테이블의 총 주문금액을 반환
// 동적 메모리 할당 실패 시 -1 반환
// 주문금액 0원 이하일 시 -1 반환
int table_order_price(int tablenum) {

	int i;
	int iter;
	iter = tables[tablenum].list_size; // 현재 테이블 주문상품 가짓수

	int* price;
	price = (int*)malloc(sizeof(int) * iter); // 상품별 가격을 저장할 배열
	if (price == NULL) { // 메모리 할당 오류
		return -1;
	}
	int* quantity;
	quantity = (int*)malloc(sizeof(int) * iter); // 상품별 수량을 저장할 배열
	if (quantity == NULL) { // 메모리 할당 오류
		return -1;
	}

	int temp, order_price; // 현재 주문액 총합 저장할 변수
	order_price = 0;
	for (i = 0; i < iter; i++) {
		price[i] = tables[tablenum].list->price;
		quantity[i] = tables[tablenum].list->sales;
		temp = price[i] * quantity[i];
		order_price = order_price + temp;
	}
	free(price);
	free(quantity);

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
int purchase_ratio_showmenu(int tablenum) {
	int order_price = table_order_price(tablenum);

	int command_num;
	int number_of_people;
	int i;
	int ratio[10];

	printf("주문 금액 확인 : %d\n", order_price);
	printf("결제할 사람 수 : ");
	scanf("%d", &number_of_people);

	if (!(number_of_people <= 2 && number_of_people >= 10)) {
		printf("오류 : 인원수는 2에서 10 사이의 정수만 가능합니다. 유효한 숫자를 입력해 주세요.\n");
		return -1;
	}
	for (i = 0; i < number_of_people;) {
		scanf("%d", &ratio[i]);
		if (!(ratio[i] >= 1 && ratio[i] <= 9)) {
			printf("오류 : 비율은 1에서 9 사이의 정수입니다. 유효한 숫자를 입력해 주세요.\n");
			continue;
			// 기획서대로는 '비율 결제 메뉴를 다시 출력' 이라고 되어 있는데 확인 필요
			// 큰 문제 없다 싶으면 현재 코드대로 비율 입력만 다시 하면 되게 하기
			// 수정해야 하면 return -1; 후 프롬프트 재실행
		}
		i++;
	}
	printf("이대로 결제 하시겠습니까?\n");
	printf("1. 결제\n");
	printf("0. 돌아가기\n");
	printf("비율 결제 - 번호 선택 > ");
	return ratio;
}

// 입력받은 비율에 따른 개개인의 결제금액을 계산하는 함수
// 파라미터는 (비율결제메뉴에서 리턴받은 비율(배열), 결제 인원수, 테이블 번호)
int calculate_ratio(int ratio[], int people_num, int tablenum) {

	int pay_sum = table_order_price(tablenum);

	int i;
	int ratio_sum = 0; // 비율의 총합
	int unit; // 비율 계산시에 사용할 단위금액
	int pay_individual[10]; // 개개인 결제 할당량

	for (i = 0; i < people_num; i++) {
		ratio_sum = ratio_sum + ratio[i];
	}

	unit = (pay_sum / 100) / ratio_sum;
	for (i = 0; i < people_num; i++) {
		pay_individual[i] = (unit * 100) * ratio[i];
		if (i > 0) {
			pay_sum -= pay_individual[i];
		}
	}
	pay_individual[0] = pay_sum;

	return pay_individual;
}

// 비율 결제_결과 출력
// 파라미터는 calculate_ratio() 와 동일 + 날짜까지
void purchase_ratio_result(int ratio[], int people_num, int tablenum, int date) {

	int* pay_individual = calculate_ratio(ratio, people_num, tablenum);

	int i;
	printf("결제가 완료되었습니다.\n");
	printf("총 결제 금액 : %d\n", table_order_price(tablenum));
	for (i = 1; i <= people_num; i++) {
		printf("%d/%d인 결제 금액 : %d\n", i, people_num, pay_individual[i - 1]);
	}
	printf("결제 일시 : %d\n", date);
	return;
}