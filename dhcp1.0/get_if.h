#ifndef _GET_IF_H_
#define _GET_IF_H_

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <errno.h>
#include "ndn_if.h"

int get_if_info(ndn_if_t * ndn_ifs)
{
    int fd;
    int interfaceNum = 0;
    struct ifreq buf[16];
    struct ifconf ifc;
    struct ifreq ifrcopy;
    char mac[16] = {0};
    char ip[32] = {0};
    char broadAddr[32] = {0};
    char subnetMask[32] = {0};

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");

        close(fd);
        return -1;
    }

    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = (caddr_t)buf;
    if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc))
    {
        interfaceNum = ifc.ifc_len / sizeof(struct ifreq);
		int if_num_i = 0;
        printf("interface num = %d\n", interfaceNum);
		for(int if_num_i = 0 ; if_num_i < interfaceNum ; if_num_i++)
        {
            printf("\ndevice name: %s\n", buf[if_num_i].ifr_name);
			memcpy(ndn_ifs[if_num_i].if_name , buf[if_num_i].ifr_name, 
					sizeof(buf[if_num_i].ifr_name)) ;
			

            //ignore the interface that not up or not runing  
            ifrcopy = buf[if_num_i];
            if (ioctl(fd, SIOCGIFFLAGS, &ifrcopy))
            {
                printf("ioctl: %s [%s:%d]\n", strerror(errno), __FILE__, __LINE__);

                close(fd);
                return -1;
            }
			if(ifrcopy.ifr_flags & IFF_RUNNING)
				printf("网卡已接上网线\n");
			else 
				printf("网卡未接上网线\n");

            //get the mac of this interface  
            if (!ioctl(fd, SIOCGIFHWADDR, (char *)(&buf[if_num_i])))
            {
                memset(mac, 0, sizeof(mac));
                snprintf(mac, sizeof(mac), "%02x:%02x:%02x:%02x:%02x:%02x",
                    (unsigned char)buf[if_num_i].ifr_hwaddr.sa_data[0],
                    (unsigned char)buf[if_num_i].ifr_hwaddr.sa_data[1],
                    (unsigned char)buf[if_num_i].ifr_hwaddr.sa_data[2],

                    (unsigned char)buf[if_num_i].ifr_hwaddr.sa_data[3],
                    (unsigned char)buf[if_num_i].ifr_hwaddr.sa_data[4],
                    (unsigned char)buf[if_num_i].ifr_hwaddr.sa_data[5]);
					
				ndn_ifs[if_num_i].mac.sa_data0 = 
					(unsigned char)buf[if_num_i].ifr_hwaddr.sa_data[0];
				ndn_ifs[if_num_i].mac.sa_data1 = 
					(unsigned char)buf[if_num_i].ifr_hwaddr.sa_data[1];
				ndn_ifs[if_num_i].mac.sa_data2 = 
					(unsigned char)buf[if_num_i].ifr_hwaddr.sa_data[2];

				ndn_ifs[if_num_i].mac.sa_data3 = 
					(unsigned char)buf[if_num_i].ifr_hwaddr.sa_data[3];
				ndn_ifs[if_num_i].mac.sa_data4 = 
					(unsigned char)buf[if_num_i].ifr_hwaddr.sa_data[4];
				ndn_ifs[if_num_i].mac.sa_data5 = 
					(unsigned char)buf[if_num_i].ifr_hwaddr.sa_data[5];
				printf("device mac: %s\n", mac);
			}
			else
			{
				printf("ioctl: %s [%s:%d]\n", strerror(errno), __FILE__, __LINE__);
				close(fd);
				return -1;
			}

			//get the IP of this interface  

			if (!ioctl(fd, SIOCGIFADDR, (char *)&buf[if_num_i]))
			{
				snprintf(ip, sizeof(ip), "%s",
						(char *)inet_ntoa(((struct sockaddr_in *)&(buf[if_num_i].ifr_addr))->sin_addr));
				printf("device ip: %s\n", ip);
			}
			else
			{
				printf("ioctl: %s [%s:%d]\n", strerror(errno), __FILE__, __LINE__);
				close(fd);
				return -1;
			}

			//get the broad address of this interface  

			if (!ioctl(fd, SIOCGIFBRDADDR, &buf[if_num_i]))
			{
				snprintf(broadAddr, sizeof(broadAddr), "%s",
						(char *)inet_ntoa(((struct sockaddr_in *)&(buf[if_num_i].ifr_broadaddr))->sin_addr));
				printf("device broadAddr: %s\n", broadAddr);
			}
			else
			{
				printf("ioctl: %s [%s:%d]\n", strerror(errno), __FILE__, __LINE__);
				close(fd);
				return -1;
			}
			//get the subnet mask of this interface  
			if (!ioctl(fd, SIOCGIFNETMASK, &buf[if_num_i]))
			{
				snprintf(subnetMask, sizeof(subnetMask), "%s",
						(char *)inet_ntoa(((struct sockaddr_in *)&(buf[if_num_i].ifr_netmask))->sin_addr));
				printf("device subnetMask: %s\n", subnetMask);
			}
			else
			{
				printf("ioctl: %s [%s:%d]\n", strerror(errno), __FILE__, __LINE__);
				close(fd);
				return -1;

			}
		}
	}
	else
	{
		printf("ioctl: %s [%s:%d]\n", strerror(errno), __FILE__, __LINE__);
		close(fd);
		return -1;
	}

	close(fd);

	return interfaceNum;
}

#endif 
