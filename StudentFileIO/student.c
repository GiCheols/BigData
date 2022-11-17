//***************************************************************
//                   HEADER FILE USED IN PROJECT
//***************************************************************

#include<conio.h>
#include<stdio.h> 
#include<stdlib.h>

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

FILE *fptr;

//***************************************************************
//        function to write in file
//****************************************************************

void write_student()	//학번 이름 입력 받기
{
	int studentNum, flag = 1;	// 학번이 이미 있는지 검사하기 위해 flag 변수 추가
	// 이미 학번이 존재한다면 flag = 0, 학번이 새로 입력하는 값이라면 flag = 1;
	int i;
	errno_t err;
	err = fopen_s(&fptr, "student.dat", "rb+");  
	// rb+: 이미 있는 학번인지 검사하기 위해 읽기 + 쓰기 모드로 file open

	printf("\nPlease Enter The New Details of student \n");
	printf("\nEnter The roll number of student ");
	scanf_s("%d", &studentNum);	// 학번 입력
	getchar(); // flushing buffer

	while (fread(&st, sizeof(st), 1, fptr) > 0) {	// 기존 학번이 있는지 확인하는 loop
		if (studentNum == st.rollno) {	// 기존 학번이 존재하는 경우
			flag = 0;
			break;
		}
		else
			flag = 1;
	}

	if (flag) {
		st.rollno = studentNum;	//신규 입력하는 학번이라면 구조체의 학번에 해당하는 레코드에 학번 저장
		printf("\n\nEnter The Name of student ");
		gets_s(st.name, sizeof(st.name));	// 이름 입력: String타입으로
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
		// fptr 파일에 st의 내용을 구조체의 크기만큼 입력
		printf("\n\nStudent Record Has Been Created.  Press any key.... ");
	}
	else	// 학번이 존재하는 경우 있다는 오류메세지와 함께 해당 함수 종료
		printf("\n\nStudent Record already Exists.   Press any Key.... ");
	fclose(fptr);
	_getch();
}


//***************************************************************
//        function to read all records from file
//****************************************************************


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

	while ( (i =  fread(&st, sizeof(st), 1, fptr)) > 0)
	{
		if (st.rollno == -1)	// 해당 학번이 삭제되었다면
			continue;	// 출력하지 않고 계속 진행
		else {
			printf("%-6d %-10s %-3d %-3d %-3.2f  %-1c\n",
				st.rollno, st.name, st.p_marks, st.c_marks, st.per, st.grade);
		}
	}
	fclose(fptr);
	_getch();
}


//***************************************************************
//        function to read specific record from file
//****************************************************************


void display_sp(int n)
{
	int flag = 0;
	errno_t err;
	err = fopen_s(&fptr, "student.dat", "rb");
	if (fptr == NULL)
		return;
	while ((fread(&st, sizeof(st), 1, fptr))>0)
	{
		if (st.rollno == -1)	
			// 해당 학번이 삭제된 레코드라면, flag를 0으로 두어 찾는 학번이 없음을 알림
			flag = 0;

		else if (st.rollno == n)
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
		printf("\n\nRecord not exist");
	_getch();
}


//***************************************************************
//        function to modify record of file
//****************************************************************


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
	while ((i = fread(&st, sizeof(st), 1, fptr))>0 && found == 0)
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
			else if (st.per >= 50 && st.per<60)
				st.grade = 'B';
			else if (st.per >= 33 && st.per<50)
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

void delete_student()	//삭제함수 수정 버전
{
	int no;
	FILE *fptr2;
	errno_t err;
	system("cls");
	printf("\n\n\n\tDelete Record");
	printf("\n\nPlease Enter The roll number of student You Want To Delete");
	scanf_s("%d", &no);

	err = fopen_s(&fptr, "student.dat", "rb+");
	if (fptr == NULL)
		return;

	//rewind(fptr);  // move file pointer to 0

	while ((fread(&st, sizeof(st), 1, fptr))>0)
	{
		if (st.rollno == no)	// 삭제하려는 학번을 찾았다면
		{
			st.rollno = -1;	// 구조체의 학번값을 -1로 바꾸고
			break;	// loop 탈출
		}
	}

	fseek(fptr, -(int)sizeof(st), 1);	// 파일 삭제 == 학번 바꾸기이므로 수정함수의 부분을 가져옴

	fwrite(&st, sizeof(st), 1, fptr);	// 원래 있던 위치에 덮어 씀

	fclose(fptr);

	printf("\n\n\tRecord Deleted ..");
	_getch();
}



//***************************************************************
//        THE MAIN FUNCTION OF PROGRAM
//****************************************************************
void main()
{
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
		case '1':
			system("cls");
			write_student();
			break;
		case '2':
			display_all();
			break;
		case '3':
			system("cls");
			printf("\n\n\tPlease Enter The roll number ");
			scanf_s("%d", &num);
			display_sp(num);
			break;
		case '4':
			modify_student(); break;
		case '5':
			delete_student(); break;
		case '6':
			break;
		default:
			printf("\a");
		}
	} while (ch != '6');
}
//***************************************************************
//                END OF PROJECT
//***************************************************************