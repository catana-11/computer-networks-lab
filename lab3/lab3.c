#include <stdio.h>
#include <math.h>


int powerOfTwo(int n)
{return (int)pow(2, n);}

void getSubnetMask(int prefix, int *m1, int *m2, int *m3, int *m4)
{
    unsigned int mask;
    if (prefix == 0)
        mask = 0;
    else
        mask = 0xFFFFFFFF << (32 - prefix);

    *m1 = (mask >> 24) & 255;
    *m2 = (mask >> 16) & 255;
    *m3 = (mask >> 8) & 255;
    *m4 = mask & 255;
}

int main()
{
    int a, b, c, d;
    int subnets;
    int borrowedBits;
    int hostBits;
    int prefix;
    int defaultPrefix;
    int m1, m2, m3, m4;
    unsigned int ip;
    unsigned int blockSize;
    unsigned int networkAddress;
    unsigned int broadcastAddress;

    int i;

    printf("\nEnter an IP Address (e.g., 192.168.1.1): ");
    scanf("%d.%d.%d.%d", &a, &b, &c, &d);

    if (a < 0 || a > 255 ||
        b < 0 || b > 255 ||
        c < 0 || c > 255 ||
        d < 0 || d > 255)
    {
        printf("\nInvalid IP Address!\n");
        return 1;
    }

    if (a >= 1 && a <= 126)
    {
        printf("\n----------------------------------------------------\n");
        printf("Class : A\n");
        printf("First Octet Decimal Range : 1 - 126\n");
        printf("First Octet Binary Pattern : 0xxxxxxx\n");
        printf("IP Range : 1.0.0.0 - 126.255.255.255\n");
        printf("Default Subnet Mask : 255.0.0.0\n");
        printf("Default Prefix : /8\n");
        printf("Hosts per Network : 2^24 - 2 = 16,777,214\n");
        printf("Number of Networks : 2^7 - 2 = 126\n");

        defaultPrefix = 8;
    }
    else if (a >= 128 && a <= 191)
    {
        printf("\n----------------------------------------------------\n");
        printf("Class : B\n");
        printf("First Octet Decimal Range : 128 - 191\n");
        printf("First Octet Binary Pattern : 10xxxxxx\n");
        printf("IP Range : 128.0.0.0 - 191.255.255.255\n");
        printf("Default Subnet Mask : 255.255.0.0\n");
        printf("Default Prefix : /16\n");
        printf("Hosts per Network : 2^16 - 2 = 65,534\n");
        printf("Number of Networks : 2^14 = 16,384\n");

        defaultPrefix = 16;
    }
    else if (a >= 192 && a <= 223)
    {
        printf("\n----------------------------------------------------\n");
        printf("Class : C\n");
        printf("First Octet Decimal Range : 192 - 223\n");
        printf("First Octet Binary Pattern : 110xxxxx\n");
        printf("IP Range : 192.0.0.0 - 223.255.255.255\n");
        printf("Default Subnet Mask : 255.255.255.0\n");
        printf("Default Prefix : /24\n");
        printf("Hosts per Network : 2^8 - 2 = 254\n");
        printf("Number of Networks : 2^21 = 2,097,152\n");

        defaultPrefix = 24;
    }
    else if (a >= 224 && a <= 239)
    {
        printf("\n----------------------------------------------------\n");
        printf("Class : D (Multicast)\n");
        printf("First Octet Decimal Range : 224 - 239\n");
        printf("First Octet Binary Pattern : 1110xxxx\n");
        printf("IP Range : 224.0.0.0 - 239.255.255.255\n");
        printf("Default Subnet Mask : N/A\n");
        printf("Hosts per Network : N/A\n");
        printf("Number of Networks : N/A\n");

        printf("\nClass D addresses are used for multicast.\n");
        printf("Subnetting calculation is not performed for Class D.\n");

        return 0;
    }
    else
    {
        printf("\n----------------------------------------------------\n");
        printf("Class : E (Experimental)\n");
        printf("First Octet Decimal Range : 240 - 255\n");
        printf("First Octet Binary Pattern : 1111xxxx\n");
        printf("IP Range : 240.0.0.0 - 255.255.255.255\n");
        printf("Default Subnet Mask : N/A\n");
        printf("Hosts per Network : N/A\n");
        printf("Number of Networks : N/A\n");

        printf("\nClass E addresses are reserved for experimental use.\n");
        printf("Subnetting calculation is not performed for Class E.\n");

        return 0;
    }


    printf("SUBNETTING CALCULATION\n");
    printf("\nEnter the number of required subnets: ");
    scanf("%d", &subnets);

    if (subnets <= 0){
        printf("\nInvalid number of subnets!\n");
        return 1;
    }

    borrowedBits = 0;

    while (powerOfTwo(borrowedBits) < subnets){
        borrowedBits++;
    }

    prefix = defaultPrefix + borrowedBits;

    if (prefix > 30){
        printf("\nCannot create %d subnets while keeping usable\n", subnets);
        printf("host addresses in every subnet.\n");
        return 1;
    }

    hostBits = 32 - prefix;
    getSubnetMask(prefix, &m1, &m2, &m3, &m4);
    int totalSubnets = powerOfTwo(borrowedBits);
    int hostsPerSubnet = powerOfTwo(hostBits) - 2;
    printf("\nOriginal Prefix        : /%d", defaultPrefix);
    printf("\nRequired Subnets       : %d", subnets);
    printf("\nBorrowed Bits          : %d", borrowedBits);
    printf("\nNew Prefix             : /%d", prefix);

    printf("\n\nSubnet Mask            : %d.%d.%d.%d",m1, m2, m3, m4);
    printf("\nNumber of Subnets      : 2^%d = %d",borrowedBits, totalSubnets);
    printf("\nHost Bits per Subnet   : %d", hostBits);
    printf("\nHosts per Subnet       : 2^%d - 2 = %d",hostBits, hostsPerSubnet);
    ip = ((unsigned int)a << 24) |
         ((unsigned int)b << 16) |
         ((unsigned int)c << 8) |
         (unsigned int)d;

    blockSize = powerOfTwo(hostBits);

    networkAddress = ip - (ip % blockSize);

    printf("\nSUBNET INFORMATION\n");

    printf("\nBlock Size : %u addresses", blockSize);

    for (i = 0; i < totalSubnets; i++){
        unsigned int currentNetwork;
        unsigned int currentBroadcast;
        unsigned int firstHost;
        unsigned int lastHost;

        currentNetwork = networkAddress + (i * blockSize);

        if (i > 0 && currentNetwork < networkAddress)
            break;

        currentBroadcast = currentNetwork + blockSize - 1;

        firstHost = currentNetwork + 1;
        lastHost = currentBroadcast - 1;

        printf("\n----------------------------------------------------\n");
        printf("Subnet %d\n", i + 1);

        printf("Network Address : %u.%u.%u.%u\n",
               (currentNetwork >> 24) & 255,
               (currentNetwork >> 16) & 255,
               (currentNetwork >> 8) & 255,
               currentNetwork & 255);

        printf("First Host      : %u.%u.%u.%u\n",
               (firstHost >> 24) & 255,
               (firstHost >> 16) & 255,
               (firstHost >> 8) & 255,
               firstHost & 255);

        printf("Last Host       : %u.%u.%u.%u\n",
               (lastHost >> 24) & 255,
               (lastHost >> 16) & 255,
               (lastHost >> 8) & 255,
               lastHost & 255);

        printf("Broadcast       : %u.%u.%u.%u\n",
               (currentBroadcast >> 24) & 255,
               (currentBroadcast >> 16) & 255,
               (currentBroadcast >> 8) & 255,
               currentBroadcast & 255);
    }
    return 0;
}