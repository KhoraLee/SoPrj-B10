#include "Util.h"

// 개행문자 전까지 입력을 읽어들임
// 메모리 누수 방지를 위해선 사용 후 free 해줘야함.
char* read_line() {
    return read_line_f(stdin);
}
 
char* read_line_f(FILE* stream) {
    int buffer_size = 16;
    int size = buffer_size;
    char* string = malloc(sizeof(char) * size); // 처음은 16자리 char 배역
    if (!string) return NULL; // 메모리 할당 실패시 NULL 반환
    int pos = 0;
    int read;

    while ((read = getc(stream)) != EOF && read != '\n') { // EOF 또는 개행 문자 전까지
        if (pos == size) { // 할당한 배열이 꽉차면
            size += buffer_size; // buffer_size만큼 크기 증가
            char* realloced = realloc(string, sizeof(char) * size); // 배열 크기 확장
            if (!realloced) {
                free(string);
                return NULL; // 확장 실패시 NULL 반환
            } else {
                string = realloced;
            }
        }
        string[pos++] = (char)read; // 읽은 문자 배열에 저장
    }

    if (pos == size) { //배열이 꽉찼다면
        char* realloced = realloc(string, sizeof(char) * (size + 1)); // 한칸 확장
        if (!realloced) {
            free(string);
            return NULL; // 확장 실패시 NULL 반환
        }
        else {
            string = realloced;
        }
    }
    string[pos] = '\0'; // 문자열 끝에 널문자 추가
    return string; // 읽은 문자열 반환
}

// 문자열 앞 뒤에서 횡공백류 제거
// <횡공백류열0><상품명><횡공백류열1><수량><횡공백류열0> 인경우 맨 앞과 맨 뒤의 <횡공백류열0>만 제거함
void trim(char* string) {
    int len = strlen(string);
    int pre = 0;
    int suf = len - 1;

    // 횡공백류가 아닌 첫번째 위치 찾기
    while (string[pre] == ' ' || string[pre] == '\t') {
         pre++;
    }

    // 횡공백류가 아닌 마지막 위치 찾기
    while (string[suf] == ' ' || string[suf] == '\t') {
        suf--;
    }

    int true_len = suf - pre + 1; // 실제 문자열 구간 길이
    memmove(string, string + pre, true_len); // 맨 앞으로 문자열 당기기
    string[true_len] = '\0';
}

// 문자열에서 모든 횡공백류를 제거
void remove_all_spaces(char* string) {
    int len = strlen(string);
    int swap = 1;
    for (int i = len - 1 ; i > 0 && swap; i--) {
        swap = 0;
        for (int j = 0; j < i; j++) {
            if(string[j] == ' ' || string[j] == '\t') {
                string[j] = string[j + 1];
                string[j + 1] = ' ';
                swap = 1;
            }
        }
    }
    trim(string);
}