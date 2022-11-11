﻿#define _CRT_SECURE_NO_WARNINGS
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
	printf("전체 block의 수 == %d\n", total_block);

	while (1) {
		printf("원하는 block의 숫자 (1~%d)를 입력하고 Enter >> ", total_block);
		scanf("%ld", &block_number);
		fflush(stdin);
		if (block_number > total_block)
			break;
		fseek(fp, sizeof(Person) * (block_number - 1), SEEK_SET);
		if (fread(&p, sizeof(Person), 1, fp) != 1) {
			printf("File Read Failure ERROR\n");
			exit(1);
		}

		printf("\n 현재 block의 위치 : %d\n", block_number);
		printf(" 이름  \t주소\t   나이\n");
		printf("%-5s %-8s %2d\n", p.name, p.address, p.age);
	}

	fclose(fp);
	return 0;
}