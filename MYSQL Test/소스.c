#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>


struct phonebook {
    char name[20];
    int tel;
};

int display_menu()
{
    int choice;

    printf("------------------------\n");
    printf("1 ------ 레코드 입력\n");
    printf("2------- 레코드 출력\n");
    printf("5------- 종료\n");
    scanf("%d", &choice);
    return choice;
}

int main() {
    FILE* fp;
    errno_t err;
    struct phonebook e;
    int i;
    int selected;

    while ((selected = display_menu()) != 5) {
        switch (selected) {
        case 1:
            err = fopen_s(&fp, "phonebook.dat", "ab");

            if (fp == NULL) {
                printf("파일을 열 수 없습니다.\n");
                return;
            }
            printf("이름과 전화번호를 입력하시오: ");
            scanf("%s %d", e.name, &e.tel);
            getchar();
            //fseek(fp, 0, SEEK_END);
            fwrite(&e, sizeof(e), 1, fp);
            fclose(fp);
            break;
        case 2:
            err = fopen_s(&fp, "phonebook.dat", "rb");
            if (fp == NULL) {
                printf("파일을 열 수 없습니다.\n");
                return;
            }
            printf("name tel\n");
            fseek(fp, 1, SEEK_SET);
            while ((i = fread(&e, sizeof(e), 1, fp)) > 0) {
                printf("%s \t%d\n", e.name, e.tel);
            }
            fclose(fp);
            break;
        case 5:
            break;
        }
    }
    return 0;

}