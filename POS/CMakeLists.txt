add_library(
	core
	STATIC
	add_product_prompts.h
	login.h
	main_prompts.h
	payment_prompts.h
	product.h
	sell_prompts.h
	settlement.h
	settlement_prompts.h
	types.h
	utils.h
	add_product_prompts.c
	login.c
	main.c
	main_prompts.c
	payment_prompts.c
	product.c
	sell_prompts.c
	settlement.c
	settlement_prompts.c
	utils.c
)

target_link_libraries(core PUBLIC dirent)

add_library(core-include INTERFACE)
target_include_directories(core-include PUBLIC .)