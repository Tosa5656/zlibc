#include <limits.h>
#include <string.h>

#include "test.h"

void test_stdio_file(void)
{
	FILE *f;
	char text[128];
	fpos_t pos;

	test_suite("stdio-file");

	remove("stdio_file.tmp");

	f = fopen("stdio_file.tmp", "w");
	CHECK(f != NULL);

	CHECK_INT(fwrite("line one\n", 1, 9, f), 9);
	CHECK_INT(puts("puts stdout") >= 0, 1);
	CHECK_INT(fputs("plain", f), 5);
	CHECK_INT(fputc('!', f), '!');
	CHECK_INT(fflush(f), 0);
	CHECK_INT(ftell(f), 15);
	fclose(f);

	f = fopen("stdio_file.tmp", "r");
	CHECK(f != NULL);

	memset(text, 0, sizeof text);
	CHECK(fgets(text, sizeof text, f) != NULL);
	CHECK_STR(text, "line one\n");

	rewind(f);
	memset(text, 0, sizeof text);
	CHECK_INT(fread(text, 1, sizeof text - 1, f), 15);
	CHECK_STR(text, "line one\nplain!");

	CHECK_INT(fseek(f, 5, SEEK_SET), 0);
	CHECK_INT(ftell(f), 5);
	memset(text, 0, sizeof text);
	CHECK_INT(fread(text, 1, 4, f), 4);
	CHECK_STR(text, "one\n");

	rewind(f);
	CHECK_INT(fgetc(f), 'l');
	CHECK_INT(ungetc('x', f), 'x');
	CHECK_INT(fgetc(f), 'x');
	CHECK_INT(fgetc(f), 'l');
	rewind(f);

	CHECK_INT(fgetpos(f, &pos), 0);
	CHECK_INT(fseek(f, 0, SEEK_END), 0);
	CHECK_INT(ftell(f), 15);
	CHECK_INT(fsetpos(f, &pos), 0);
	CHECK_INT(ftell(f), 0);

	CHECK_INT(fclose(f), 0);

	f = fopen("stdio_file.tmp", "w");
	CHECK(f != NULL);
	CHECK_INT(ftell(f), 0);
	fclose(f);

	f = fopen("stdio_file.tmp", "r");
	CHECK(f != NULL);
	CHECK_INT(fgetc(f), EOF);
	CHECK(feof(f) != 0);
	fclose(f);

	f = fopen("stdio_file.tmp", "a");
	CHECK(f != NULL);
	CHECK_INT(fputs("app", f), 3);
	fclose(f);

	f = fopen("stdio_file.tmp", "r");
	CHECK(f != NULL);
	memset(text, 0, sizeof text);
	CHECK(fgets(text, sizeof text, f) != NULL);
	CHECK_STR(text, "app");
	fclose(f);

	f = fopen("stdio_file.tmp", "r+");
	CHECK(f != NULL);
	CHECK_INT(fputs("XYZ", f), 3);
	rewind(f);
	memset(text, 0, sizeof text);
	CHECK_INT(fread(text, 1, 3, f), 3);
	CHECK_STR(text, "XYZ");
	fclose(f);

	CHECK(fopen("stdio_missing_xyz.tmp", "r") == NULL);

	f = tmpfile();
	CHECK(f != NULL);
	CHECK_INT(fputs("tmp body", f), 8);
	rewind(f);
	memset(text, 0, sizeof text);
	CHECK_INT(fread(text, 1, 8, f), 8);
	CHECK_STR(text, "tmp body");
	fclose(f);

	CHECK(remove("stdio_file.tmp") == 0);
}
