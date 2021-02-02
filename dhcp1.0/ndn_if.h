// create by weiguohua
#ifndef _NDN_IF_
#define _NDN_IF_

#define NDN_IF_NAMESIZE 100
#define NDN_NAME_LEN 300

typedef struct hw_addr{
	unsigned char sa_data0 ;
	unsigned char sa_data1 ;
	unsigned char sa_data2 ;
	unsigned char sa_data3 ;
	unsigned char sa_data4 ;
	unsigned char sa_data5 ;
}hw_addr_t ;

typedef struct ndn_if{
	char if_name[NDN_IF_NAMESIZE];
	hw_addr_t mac ;
	char ndn_name[NDN_NAME_LEN];
	char ndn_gw[NDN_NAME_LEN];
}ndn_if_t;

#endif 
