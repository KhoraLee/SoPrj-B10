#ifndef product_management_prompts_h
#define product_management_prompts_h

void product_management_prompts();

void add_product_prompt(void);

void remove_product_prompt();

void remove_product(int idx);

int read_name(char* np);

int read_price(int* pp);

#endif
