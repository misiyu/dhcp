// create by weiguohua
#include <stdio.h>
#include <net/if.h>
int main() {

	struct ifreq ifr ;
	int skfd = sockets(AF_PACKET , SOCK_RAW , 0);
	return 0;
}
