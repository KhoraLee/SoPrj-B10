#ifndef product_h
#define product_h

#include <stdio.h>

int read_product_file(void);
int readproductline(FILE* fp);
int productcmp(char* name);
void addproduct(char* name, int price);
#endif
