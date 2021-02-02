// create by weiguohua
#ifndef _DHCP_NET_
#define _DHCP_NET_

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

#define ETH_P_NARP 0x8625
#define DHCP_DISCOVER 0

class DHCP_net{

public:
	static int send_discover(char *if_name , unsigned char *mac){
		uint8_t ether_frame[IP_MAXPACKET];
		struct sockaddr_ll sockaddr ;	
		unsigned char dst_mac[6] = {0xff,0xff,0xff,0xff,0xff,0xff};
		get_sockaddr(&sockaddr,if_name);
		memcpy(sockaddr.sll_addr , mac , 6);
		int datalen = 1 ;
		char data = DHCP_DISCOVER ;
		int frame_length = 6+6+2+datalen ;
		memcpy(ether_frame,dst_mac,6);
		memcpy(ethernetame+6,mac,6);
		ether_frame[12] = (ETH_P_NARP >> 8);
		ether_frame[13] = (ETH_P_NARP & 0xff);
		ether_frame[14] = data ;
		return 0 ;
	}

	static int get_sockaddr(struct sockaddr_ll *sockaddr_p, char *if_name){
			
		memset(sockaddr_p , 0 , sizeof(*sockaddr_p));
		if((sockaddr_p->sll_ifindex = if_nametoindex(if_name)) == 0){
			perror ("if_nametoindex() failed to obtain interface index ");
			exit (EXIT_FAILURE);
		}
		sockaddr_p->sll_family = AF_PACKET ;
		sockaddr_p->sll_halen(6);
		return 0 ;
	}

	static int send_frame(uint8_t *ether_frame , int frame_length,
			struct sockaddr_ll *sockaddr){

		if ((sd = socket (PF_PACKET, SOCK_RAW, htons (ETH_P_NDN))) < 0) {
			perror ("socket() failed ");
			exit (EXIT_FAILURE);
		}
		if ((bytes = sendto (sd, ether_frame, frame_length, 0, 
						(struct sockaddr *) sockaddr, sizeof (sockaddr))) <= 0) {
			perror ("sendto() failed");
			exit (EXIT_FAILURE);
		}
		close (sd);
		return 0 ;
	}

	

};

#endif 
