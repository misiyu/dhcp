#include <stdio.h>
int main() {

	FILE *fp = popen("ip link","r");
	char buff[1000];
	fgets(buff,1000,fp);
	printf("%s",buff);
	pclose(fp);
	return 0;
}
