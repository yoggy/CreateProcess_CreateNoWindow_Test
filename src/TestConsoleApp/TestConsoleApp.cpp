#include <SDKDDKVer.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[])
{	
	time_t t;
	struct tm d;
	char buf[128];
	FILE *fp = NULL;

	time(&t);
	localtime_s(&d, &t);
	strftime(buf, 123, "%Y/%m/%d-%H:%M:%S", &d);

	printf("TestConsoleApp.exe : touch _hoge.txt %s\n", buf);
	
	fopen_s(&fp, "_hoge.txt", "w");
	fprintf(fp, "TestConsoleApp.exe : touch _hoge.txt %s\n", buf);
	for (int i = 1; i < argc; ++i) {
		fprintf(fp, "\argv[%d] = %s\n", i, argv[i]);
	}

	fclose(fp);

	return 0;
}

