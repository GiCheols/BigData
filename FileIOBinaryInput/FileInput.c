#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char name[10];
	char address[100];
	int age;
}Person;

int main() {
	FILE* fp;
	Person p;
	fp = fopen("person.bin", "wb");

	if (fp == NULL) {
		printf("File Open Failure ERROR!\n");
		exit(1);
	}

	for (int i = 0; i < 2; i++) {
		printf("�̸��� �Է��ϼ���: ");
		gets(p.name);
		printf("�ּҸ� �Է��ϼ���: ");
		gets(p.address);
		printf("���̸� �Է��ϼ���: ");
		scanf("%d", &p.age);
		getchar();

		if (fwrite(&p, sizeof(Person), i, fp) != i) {
			printf("File Write Failure ERROR\n");
			exit(1);
		}
	}
	fclose(fp);

	fp = fopen("person.bin", "rb");
	long total_block, block_number;
	fseek(fp, 0, SEEK_END);
	total_block = ftell(fp) / sizeof(Person);
	printf("��ü block�� �� == %d\n", total_block);

	while (1) {
		printf("���ϴ� block�� ���� (1~%d)�� �Է��ϰ� Enter >> ", total_block);
		scanf("%ld", &block_number);
		fflush(stdin);
		if (block_number > total_block)
			break;
		fseek(fp, sizeof(Person) * (block_number - 1), SEEK_SET);
		if (fread(&p, sizeof(Person), 1, fp) != 1) {
			printf("File Read Failure ERROR\n");
			exit(1);
		}

		printf("\n ���� block�� ��ġ : %d\n", block_number);
		printf(" �̸�  \t�ּ�\t   ����\n");
		printf("%-5s %-8s %2d\n", p.name, p.address, p.age);
	}
	fclose(fp);
	return 0;
}