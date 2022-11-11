#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char name[10];
	char address[20];
	int age;
}Person;

int main() {
	FILE* fp;
	Person p;
	long total_block, block_number;
	fp = fopen("person.bin", "rb");

	if (fp == NULL) {
		printf("File Open Failure ERROR!\n");
		exit(1);
	}

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