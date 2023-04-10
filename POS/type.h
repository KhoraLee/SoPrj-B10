#pragma once

typedef struct _product {
    char name[16]; // 상품 명, 15 글자 + \0
    int price; // 가격
    int sales; // 금일 총 판매 갯수
} Product;

typedef struct _all_product {
    Product* list; // 모든 상품들을 포함한 Array
    int list_size; // Array Size
} All_Product;

typedef struct _table {
    Product* list; // malloc 으로 배열 할당 후 추가 주문마다 realloc
    int list_size; // 주문한 상품 갯수
} Table;