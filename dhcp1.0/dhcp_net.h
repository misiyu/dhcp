// create by weiguohua
#ifndef _DHCP_NET_H_
#define _DHCP_NET_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <bits/ioctls.h>
#include <net/if.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <errno.h>
#define ETH_P_NDN_DHCP	0x8625
#define DISCOVER	0
#define OFFER		1
#define REQUEST		2
#define ACK			3

int discover(char *ifr_name_w){
		
}

int offer(char *ifr_name_w ){

}

int request(char *ifr_name_w , char *ndn_name){

}

int ack(char *ifr_name_w){
}


void *client_recv(void *var){
}

void *server_recv(void *var){
}

#endif 
