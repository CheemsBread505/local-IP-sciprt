#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <net/if.h>

int main(int argc, char *argv[])
{
    struct ifaddrs *addrs, *tmp;
    getifaddrs(&addrs);
    tmp = addrs;

    while (tmp)
    {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET && !(tmp->ifa_flags & IFF_LOOPBACK))
        {
            struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
            char str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &pAddr->sin_addr, str, sizeof str);
            printf("Local IP: %s\n", str);
            break;
        }

        tmp = tmp->ifa_next;
    }

    freeifaddrs(addrs);
    return 0;
}

