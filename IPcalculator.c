#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h> // Para inet_addr
/* La red se obtiene comparando con & la IP con la máscara
Para el rango, como en la mascara las subredes libres se representan con "0",
lo que estamos haciendo es invertirla, los 0 serán 1 y viceversa, obteniendo 
el rango total de direcciones que se pueden asignar.
Para la inversión, comparamos con XOR la máscara y 0xFFFFFFFF
que es  en hexadecimal el mayor número representable con 32 bits */

void get_IP_range(unsigned long ip, unsigned long mask) 
{
    unsigned long red = ip & mask;

    unsigned long first = red + 1;

    unsigned long range = (mask ^ 0xFFFFFFFF);
    unsigned long last = red + range;

    struct in_addr red_addr, first_addr, last_addr;
    red_addr.s_addr = htonl(red);
    first_addr.s_addr = htonl(first);
    last_addr.s_addr = htonl(last);
    char first_addr_str[INET_ADDRSTRLEN];
    char last_addr_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(first_addr), first_addr_str, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &(last_addr), last_addr_str, INET_ADDRSTRLEN);
    printf("network: %s\n", inet_ntoa(red_addr));

    printf("usable IPs: %s - %s\n", first_addr_str, last_addr_str);
}

int main(int argc, char *argv[]) {
    // Verificar que se proporcionen suficientes argumentos
    if (argc != 3) {
        printf("Usage: %s <IP adress> <subnet-mask>\n", argv[0]);
        return 1;
    }
    get_IP_range(ntohl(inet_addr(argv[1])), ntohl(inet_addr(argv[2])));

    return 0;
}