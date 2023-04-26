#ifndef types_h
#define types_h

typedef struct _product {
    char name[16]; // 상품 명, 15 글자 + \0
    int price; // 가격
    int amount; // 금일 총 판매 갯수
} Product;

typedef struct _prodcut_arr {
    Product* products; // malloc 으로 배열 할당 후 추가시마다 realloc
    int length; // Array 크기
} Product_Array;

typedef Product_Array Table;

#endif
