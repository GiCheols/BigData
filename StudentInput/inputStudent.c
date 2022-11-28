#include <stdio.h>
#include <mysql.h>

int main(int argc, char** argv) {
	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;
	int fields, cnt;

	conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, "localhost", "root", "rlcjf010331.", "studentdb", 0, NULL, 0)) {
		printf("%s\n", mysql_error(conn));
		exit(1);
	}

	mysql_set_character_set(conn, "euckr");

	if (mysql_query(conn, "SELECT * FROM student")) {
		printf("%s\n", mysql_error(conn));
		exit(1);
	}

	res = mysql_store_result(conn);

	fields = mysql_num_fields(res);

	while ((row = mysql_fetch_row(res))) {
		for (cnt = 0; cnt < fields; ++cnt)
			printf("%12s ", row[cnt]);
		printf("\n");
	}

	mysql_free_result(res);
	mysql_close(conn);
}