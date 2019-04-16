#include "get_if.h"
#include "ndn_if.h"
#include "dhcp_net.h"

#define IF_MAX_N 30
static ndn_if_t ndn_ifs[IF_MAX_N];
static int if_num ;
  
int main(void)
{
	if_num = get_if_info(ndn_ifs);
	/*while(1){*/

	/*}*/
	int i = 0;
	printf("============================\n");
	for (i = 0; i < if_num; ++i) {
		printf("if_name = %s\n", ndn_ifs[i].if_name);
		printf("	mac = %02x:%02x:%02x:%02x:%02x:%02x \n", 
				ndn_ifs[i].mac.sa_data0,
				ndn_ifs[i].mac.sa_data1,
				ndn_ifs[i].mac.sa_data2,
				ndn_ifs[i].mac.sa_data3,
				ndn_ifs[i].mac.sa_data4,
				ndn_ifs[i].mac.sa_data5
				);
	}
    return 0;
}
