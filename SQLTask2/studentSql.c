//***************************************************************
//                   HEADER FILE USED IN PROJECT
//***************************************************************
#define _CRT_SECURE_NO_WARNINGS
#include<conio.h>
#include<stdio.h> 
#include<stdlib.h>
#include <mysql.h>
#include <errno.h>

//***************************************************************
//                   STURUCTURE USED IN PROJECT
//****************************************************************

struct student
{
	int rollno;
	char name[50];
	int p_marks, c_marks;
	double per;
	char grade;
}st;

//***************************************************************
//        global declaration
//****************************************************************

MYSQL* mysql;
FILE* fptr;

//***************************************************************
//        function to write in MySQL
//****************************************************************

void finishWithError(MYSQL* mysql) {
	fprintf(stderr, "%s\n", mysql_error(mysql));
	mysql_close(mysql);
	exit(1);
}

void writeStudent() {
	char query[200];
	int rollno, p_marks, c_marks;
	char grade;
	char name[20];
	double per;
	printf("\nPlease Enter The New Details of student \n");
	printf("\nEnter The roll number of student ");
	scanf_s("%d", &rollno);
	getchar(); // flushing buffer
	printf("\n\nEnter The Name of student ");
	gets_s(name, sizeof(name));
	printf("\nEnter The marks in physics out of 100 : ");
	scanf_s("%d", &p_marks);
	printf("\nEnter The marks in chemistry out of 100 : ");
	scanf_s("%d", &c_marks);

	per = (p_marks + c_marks) / 2.0;
	if (per >= 60)
		grade = 'A';
	else if (per >= 50 && per < 60)
		grade = 'B';
	else if (per >= 33 && per < 50)
		grade = 'C';
	else
		grade = 'F';

	sprintf(query, "insert into student values(%d, \"%s\", %d, %d, %2f, \"%c\")", rollno, name, p_marks, c_marks, per, grade);

	if (mysql_query(mysql, query)) {
		finishWithError(mysql);
		exit(1);
	}
	printf("\n\nStudent Record Has Been Created.  Press any key.... ");
	_getch();
}

void write_student()
{
	errno_t err;
	err = fopen_s(&fptr, "student.dat", "ab");  //return 0 if success
	printf("\nPlease Enter The New Details of student \n");
	printf("\nEnter The roll number of student ");
	scanf_s("%d", &st.rollno);
	getchar(); // flushing buffer
	printf("\n\nEnter The Name of student ");
	gets_s(st.name, sizeof(st.name));
	printf("\nEnter The marks in physics out of 100 : ");
	scanf_s("%d", &st.p_marks);
	printf("\nEnter The marks in chemistry out of 100 : ");
	scanf_s("%d", &st.c_marks);

	st.per = (st.p_marks + st.c_marks) / 2.0;
	if (st.per >= 60)
		st.grade = 'A';
	else if (st.per >= 50 && st.per < 60)
		st.grade = 'B';
	else if (st.per >= 33 && st.per < 50)
		st.grade = 'C';
	else
		st.grade = 'F';
	fwrite(&st, sizeof(st), 1, fptr);
	fclose(fptr);
	printf("\n\nStudent Record Has Been Created.  Press any key.... ");
	_getch();
}

//***************************************************************
//        function to read all records from file
//****************************************************************

void displayAll()
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	int fields, cnt;

	mysql_set_character_set(mysql, "euckr");
	system("cls");
	printf("\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n");
	printf("===================================================================\n");
	printf("        R.No.       Name       P       C      Ave          Grade\n");
	printf("===================================================================\n");
	if (mysql_query(mysql, "SELECT * FROM student"))
	{
		printf("%s\n", mysql_error(mysql));
		exit(1);
	}

	res = mysql_store_result(mysql);
	fields = mysql_num_fields(res);
	while ((row = mysql_fetch_row(res))) {
		for (cnt = 0; cnt < fields; ++cnt)
			printf("%12s ", row[cnt]);
		printf("\n");
	}
	mysql_free_result(res);
	getchar();
}

void display_all()
{
	errno_t err; int i;
	system("cls");
	printf("\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n");
	printf("====================================================\n");
	printf("R.No.  Name       P   C   Ave   Grade\n");
	printf("====================================================\n");

	err = fopen_s(&fptr, "student.dat", "rb");
	if (fptr == NULL)
		return;

	while ((i = fread(&st, sizeof(st), 1, fptr)) > 0)
	{
		printf("%-6d %-10s %-3d %-3d %-3.2f  %-1c\n",
			st.rollno, st.name, st.p_marks, st.c_marks, st.per, st.grade);
	}
	fclose(fptr);
	_getch();
}

//***************************************************************
//        function to read specific record from file
//****************************************************************

void displaySp(int rollno)
{

	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[200];
	int fields;
	int cnt;
	mysql_set_character_set(mysql, "euckr");
	sprintf(query, "select * from student where rollno = %d", rollno);
	if (mysql_query(mysql, query)) {
		printf("%s\n", mysql_error(mysql));
		exit(1);
	}
	res = mysql_store_result(mysql);
	fields = mysql_num_fields(res);
	row = mysql_fetch_row(res);

	if (row == NULL)
		printf("\n\nrecord not exist");
	else {
		for (cnt = 0; cnt < fields; ++cnt) {
			printf("%12s ", row[cnt]);
			printf("\n");
			system("cls");
			printf("\nRoll number of student : %s", row[0]);
			printf("\nName of student : %s", row[1]);
			printf("\nMarks in Physics : %s", row[2]);
			printf("\nMarks in Chemistry : %s", row[3]);
			printf("\nPercentage of student is  : %s", row[4]);
			printf("\nGrade of student is : %s", row[5]);
		}
	}
	mysql_free_result(res);
	_getch();
}

void display_sp(int n)
{
	int flag = 0;
	errno_t err;
	err = fopen_s(&fptr, "student.dat", "rb");
	if (fptr == NULL)
		return;
	while ((fread(&st, sizeof(st), 1, fptr)) > 0)
	{
		if (st.rollno == n)
		{
			system("cls");
			printf("\nRoll number of student : %d", st.rollno);
			printf("\nName of student : %s", st.name);
			printf("\nMarks in Physics : %d", st.p_marks);
			printf("\nMarks in Chemistry : %d", st.c_marks);
			printf("\nPercentage of student is  : %.2f", st.per);
			printf("\nGrade of student is : %c", st.grade);
			flag = 1;
		}
	}
	fclose(fptr);
	if (flag == 0)
		printf("\n\nrecord not exist");
	_getch();
}

//***************************************************************
//        function to modify record of file
//****************************************************************

void modifyStudent() {
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[200];
	int fields, rollno;
	double per;
	char name[20];
	char grade;
	int p_marks, c_marks;

	system("cls");
	printf("\n\n\tTo Modify ");
	printf("\n\n\tPlease Enter The roll number of student");
	scanf("%d", &rollno);
	getchar();


	mysql_set_character_set(mysql, "euckr");
	sprintf(query, "select * from student where rollno = %d", rollno);
	if (mysql_query(mysql, query)) {
		printf("%s\n", mysql_error(mysql));
		exit(1);
	}
	res = mysql_store_result(mysql);
	fields = mysql_num_fields(res);
	row = mysql_fetch_row(res);


	if (row == NULL)
		printf("\n\nrecord not exist");

	else {
		printf("\nRoll number of student : %s", row[0]);
		printf("\nName of student : %s", row[1]);
		printf("\nMarks in Physics : %s", row[2]);
		printf("\nMarks in Chemistry : %s", row[3]);
		printf("\nPercentage of student is  : %s", row[4]);
		printf("\nGrade of student is : %s", row[5]);
	}

	printf("\nPlease Enter The New Details of student \n");
	printf("\nEnter The roll number of student ");
	scanf_s("%d", &rollno);
	getchar(); // flushing buffer
	printf("\n\nEnter The Name of student ");
	gets_s(name, sizeof(name));
	printf("\nEnter The marks in physics out of 100 : ");
	scanf_s("%d", &p_marks);
	printf("\nEnter The marks in chemistry out of 100 : ");
	scanf_s("%d", &c_marks);

	per = (p_marks + c_marks) / 2.0;
	if (per >= 60)
		grade = 'A';
	else if (per >= 50 && per < 60)
		grade = 'B';
	else if (per >= 33 && per < 50)
		grade = 'C';
	else
		grade = 'F';

	sprintf(query, "update student set name = \'%s\', p_marks = %d, c_marks = %d, per = %2f, grade = \'%c\' where rollno = %d", name, p_marks, c_marks, per, grade, rollno);
	mysql_query(mysql, query);
	if (mysql_query(mysql, query)) {
		finishWithError(mysql);
		exit(1);
	}
	printf("\n\nStudent Record Updated");
	_getch();
}

void modify_student()
{
	int no, found = 0, i;
	errno_t err;
	system("cls");
	printf("\n\n\tTo Modify ");
	printf("\n\n\tPlease Enter The roll number of student");
	scanf_s("%d", &no);
	err = fopen_s(&fptr, "student.dat", "rb+");
	if (fptr == NULL)
		return;
	while ((i = fread(&st, sizeof(st), 1, fptr)) > 0 && found == 0)
	{
		if (st.rollno == no)
		{
			printf("\nRoll number of student : %d", st.rollno);
			printf("\nName of student : %s", st.name);
			printf("\nMarks in Physics : %d", st.p_marks);
			printf("\nMarks in Chemistry : %d", st.c_marks);
			printf("\nPercentage of student is  : %.2f", st.per);
			printf("\nGrade of student is : %c", st.grade);
			printf("\nPlease Enter The New Details of student \n");
			printf("\nEnter The roll number of student ");
			scanf_s("%d", &st.rollno);
			getchar();  //flushing buffer (fflsh는 작동안함)
			printf("\n\nEnter The Name of student ");
			gets_s(st.name, sizeof(st.name));
			printf("\nEnter The marks in physics out of 100 : ");
			scanf_s("%d", &st.p_marks);
			printf("\nEnter The marks in chemistry out of 100 : ");
			scanf_s("%d", &st.c_marks);

			st.per = (st.p_marks + st.c_marks) / 2.0;
			if (st.per >= 60)
				st.grade = 'A';
			else if (st.per >= 50 && st.per < 60)
				st.grade = 'B';
			else if (st.per >= 33 && st.per < 50)
				st.grade = 'C';
			else
				st.grade = 'F';


			fseek(fptr, -(int)sizeof(st), 1);  // SEEK_CUR

			fwrite(&st, sizeof(st), 1, fptr);


			printf("\n\n\t Record Updated");

			found = 1;
			break;
		}
	}

	fclose(fptr);
	if (found == 0)
		printf("\n\n Record Not Found ");
	_getch();
}

//***************************************************************
//        function to delete record of file
//****************************************************************

void deleteStudent() {
	int rollno;
	char query[200];
	system("cls");
	printf("\n\n\n\tDelete Record");
	printf("\n\nPlease Enter The roll number of student You Want To Delete");
	scanf("%d", &rollno);
	getchar();
	sprintf_s(query, sizeof(query), "delete from student where rollno = %d", rollno);
	if (mysql_query(mysql, query)) {
		finishWithError(mysql);
		exit(1);
	}
	printf("\n\n\tRecord Deleted ..");
	_getch();
}

void delete_student()
{
	int no;
	FILE* fptr2;
	errno_t err;
	system("cls");
	printf("\n\n\n\tDelete Record");
	printf("\n\nPlease Enter The roll number of student You Want To Delete");
	scanf_s("%d", &no);

	err = fopen_s(&fptr, "student.dat", "rb");
	if (fptr == NULL)
		return;
	err = fopen_s(&fptr2, "Temp.dat", "wb");
	rewind(fptr);  // move file pointer to 0

	while ((fread(&st, sizeof(st), 1, fptr)) > 0)
	{
		if (st.rollno != no)
		{
			fwrite(&st, sizeof(st), 1, fptr2);
		}
	}
	fclose(fptr2);
	fclose(fptr);
	remove("student.dat");
	rename("Temp.dat", "student.dat");
	printf("\n\n\tRecord Deleted ..");
	_getch();
}

//***************************************************************
//        THE MAIN FUNCTION OF PROGRAM
//****************************************************************

void main()
{
	mysql = mysql_init(NULL);
	if (!mysql_real_connect(mysql, "localhost", "root", "rlcjf010331.", "studentdb", 0, NULL, 0)) {
		finishWithError(mysql);
	}

	char ch;
	int num;
	do
	{
		system("cls");

		printf("\n\n\t1.CREATE STUDENT RECORD");
		printf("\n\n\t2.DISPLAY ALL STUDENTS RECORDS");
		printf("\n\n\t3.SEARCH STUDENT RECORD ");
		printf("\n\n\t4.MODIFY STUDENT RECORD");
		printf("\n\n\t5.DELETE STUDENT RECORD");
		printf("\n\n\t6.EXIT");
		printf("\n\n\tPlease Enter Your Choice (1-6) ");
		ch = _getche();

		switch (ch)
		{
		case '1':	system("cls");
			writeStudent();
			break;
		case '2':	displayAll();
			break;
		case '3':	system("cls");
			printf("\n\n\tPlease Enter The roll number ");
			scanf("%d", &num);
			getchar();
			displaySp(num);
			break;
		case '4':	modifyStudent(); break;
		case '5':	deleteStudent(); break;
		case '6':	break;
		default:	printf("\a");
		}
	} while (ch != '6');
}
//***************************************************************
//                END OF PROJECT
//***************************************************************