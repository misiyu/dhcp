// create by weiguohua
#ifndef _IF_INFO_
#define _IF_INFO_

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX_IF_NAME 100
#define MAX_NDN_NAME 300
#define IF_MAX_N 30
enum IF_STATE  {off,init,active} ;

typedef struct ndn_if{
	char if_name[MAX_IF_NAME];
	unsigned char mac[6];
	char ndn_name ;
	char ndn_gw[MAX_NDN_NAME] ;
	IF_STATE state ;
}ndn_if_t ;

class If_info{

private:
	int if_n ;
	ndn_if_t ndn_ifs[IF_MAX_N] ;
public:
	If_info();
	int get_if_info();
	int add_if(const char *if_name , unsigned char *mac , IF_STATE state);
	
};

#endif 
