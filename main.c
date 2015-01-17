#include <stdio.h>
#include <stdlib.h>

#include <malloc.h>
#include <string.h>

#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>


int main(int argc, char** argv)
{
    struct sockaddr_in addr;
    struct icmphdr icmp_hdr;
    char packetdata[sizeof(icmp_hdr) + 5];

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP);

    if(sock < 0)
    {
        printf("sock() errno: %i\n", errno);

	return EXIT_FAILURE;
    }


    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(0x7F000001);

    memset(&icmp_hdr, 0, sizeof(icmp_hdr));
    icmp_hdr.type = ICMP_ECHO;
    icmp_hdr.un.echo.id = 1234;
    icmp_hdr.un.echo.sequence = 1;

    memcpy(packetdata, &icmp_hdr, sizeof(icmp_hdr));
    memcpy(packetdata + sizeof(icmp_hdr), "12345", 5);

    if(sendto(sock, packetdata, sizeof(packetdata), 0, (struct sockaddr*) &addr, sizeof(addr)) < 0)
    {
        printf("sendto() errno: %i\n", errno);

	return EXIT_SUCCESS;
    }
    

    printf("ICMP sent");

    return EXIT_SUCCESS;
}
