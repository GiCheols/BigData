#include <stdio.h>
#include <mysql.h>

void main() {
	printf("%s\n\n", mysql_get_client_info());
}

/*
프로젝트 속성 - VC++ 디렉터리 - 포함 디렉터리에 다음을 추가:
	C:\Program Files\MySQL\MySQL Server 8.0\include;
라이브러리 디렉터리에 다음을 추가:
	C:\Program Files\MySQL\MySQL Server 8.0\lib;
속성 페이지 링커 - 입력 - 추가 종속성에 다음을 추가:
	libmysql.lib;
속성 페이지 디버깅 - 환경에 다음을 추가:
	PATH=%PATH%;C:\Program Files\MySQL\MySQL Server 8.0\lib;C:\Program Files\MySQL\MySQL Server 8.0\bin;
이 후 main() 실행하면 성공적으로 MySQL 버전이 나옴
*/