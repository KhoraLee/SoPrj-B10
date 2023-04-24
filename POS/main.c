#include "utils.h"
#include "types.h"
#include "login.h"
#include "prompts.h"

Table tables[4]; // 테이블 4개
Product_Array all_products; // 모든 상품들의 목록을 포함한 구조체
char base_dir[FILENAME_MAX];
int date; // 로그인된 날짜

extern int latest_login_date; // 로그인 실패시 사용, 가장 최근 로그인 날짜

int main() {
    get_current_dir(base_dir);
    
    // 로그인
    while (1) {
        printf("POS / 로그인 메뉴 – 날짜 입력>");
        char *input = read_line();
        trim(input);
        int result = process_login(input);
        if (result == -1) {
            printf("오류 : YYYYMMDD 혹은 YYMMDD형식으로 입력해주십시오.\n");
        } else if (result == -2) {
            printf("오류 : 그레고리력에 존재하지 않는 날짜입니다.\n");
        } else if (result == -3) {
            printf("오류 : 데이터 파일 위치 %s에 %d 파일이 존재합니다. 마지막 정산일 이후의 날 짜로만 로그인 할 수 있습니다.\n", base_dir, latest_login_date);
        } else if (result == -4) {
            int year = latest_login_date / 10000;
            int month = (latest_login_date / 100) - year * 100;
            int date = latest_login_date % 100;
            printf("로그인 실패: 마지막 로그인 날짜가 %d년 %d월 %d일입니다. 마지막 정산일 이후의 날짜로만 로그인 할 수 있습니다.\n", year, month, date);
        } else {
            date = result; // 로그인 날짜 저장
            break;
        }
    }
    
    // 메인 프롬프트로
    main_prompt();
}
