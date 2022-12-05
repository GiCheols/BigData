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
    printf("1 ------ ���ڵ� �Է�\n");
    printf("2------- ���ڵ� ���\n");
    printf("5------- ����\n");
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
                printf("������ �� �� �����ϴ�.\n");
                return;
            }
            printf("�̸��� ��ȭ��ȣ�� �Է��Ͻÿ�: ");
            scanf("%s %d", e.name, &e.tel);
            getchar();
            //fseek(fp, 0, SEEK_END);
            fwrite(&e, sizeof(e), 1, fp);
            fclose(fp);
            break;
        case 2:
            err = fopen_s(&fp, "phonebook.dat", "rb");
            if (fp == NULL) {
                printf("������ �� �� �����ϴ�.\n");
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