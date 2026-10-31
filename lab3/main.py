def power_of_two(n):
    return 2 ** n

#prefix to subnet mask

def get_subnet_mask(prefix):

    if prefix == 0:
        mask = 0
    else:
        mask = (0xFFFFFFFF << (32 - prefix)) & 0xFFFFFFFF

    # extract each 8bit octet from the 32bit mask
    m1 = (mask >> 24) & 255
    m2 = (mask >> 16) & 255
    m3 = (mask >> 8) & 255
    m4 = mask & 255

    return m1, m2, m3, m4


# convert a 32bit int back into dotted decimal IP format
def int_to_ip(ip):
    a = (ip >> 24) & 255
    b = (ip >> 16) & 255
    c = (ip >> 8) & 255
    d = ip & 255

    return f"{a}.{b}.{c}.{d}"


#MAIN

ip_input = input("\nenter an ip address (e.g., 192.168.1.1): ")
octets = list(map(int, ip_input.split(".")))

# check if ip contains exactly 4 valid octets
if len(octets) != 4 or any(x < 0 or x > 255 for x in octets):
    print("\nInvalid IP Address!")
    exit()

a, b, c, d = octets


#IP ADDRESS CLASS

if 1 <= a <= 126:
    print("\n----------------------------------------------------")
    print("Class : A")
    print("First Octet Decimal Range : 1 - 126")
    print("First Octet Binary Pattern : 0xxxxxxx")
    print("IP Range : 1.0.0.0 - 126.255.255.255")
    print("Default Subnet Mask : 255.0.0.0")
    print("Default Prefix : /8")
    print("Hosts per Network : 2^24 - 2 = 16,777,214")
    print("Number of Networks : 2^7 - 2 = 126")

    default_prefix = 8

elif 128 <= a <= 191:
    print("\n----------------------------------------------------")
    print("Class : B")
    print("First Octet Decimal Range : 128 - 191")
    print("First Octet Binary Pattern : 10xxxxxx")
    print("IP Range : 128.0.0.0 - 191.255.255.255")
    print("Default Subnet Mask : 255.255.0.0")
    print("Default Prefix : /16")
    print("Hosts per Network : 2^16 - 2 = 65,534")
    print("Number of Networks : 2^14 = 16,384")

    default_prefix = 16

elif 192 <= a <= 223:
    print("\n----------------------------------------------------")
    print("Class : C")
    print("First Octet Decimal Range : 192 - 223")
    print("First Octet Binary Pattern : 110xxxxx")
    print("IP Range : 192.0.0.0 - 223.255.255.255")
    print("Default Subnet Mask : 255.255.255.0")
    print("Default Prefix : /24")
    print("Hosts per Network : 2^8 - 2 = 254")
    print("Number of Networks : 2^21 = 2,097,152")

    default_prefix = 24

elif 224 <= a <= 239:
    print("\n----------------------------------------------------")
    print("Class : D (Multicast)")
    print("First Octet Decimal Range : 224 - 239")
    print("First Octet Binary Pattern : 1110xxxx")
    print("IP Range : 224.0.0.0 - 239.255.255.255")
    print("Default Subnet Mask : N/A")
    print("Hosts per Network : N/A")
    print("Number of Networks : N/A")

    print("\nClass D addresses are used for multicast.")
    print("Subnetting calculation is not performed for Class D.")
    exit()

else:
    print("\n----------------------------------------------------")
    print("Class : E (Experimental)")
    print("First Octet Decimal Range : 240 - 255")
    print("First Octet Binary Pattern : 1111xxxx")
    print("IP Range : 240.0.0.0 - 255.255.255.255")
    print("Default Subnet Mask : N/A")
    print("Hosts per Network : N/A")
    print("Number of Networks : N/A")

    print("\nClass E addresses are reserved for experimental use.")
    print("Subnetting calculation is not performed for Class E.")
    exit()


# SUBNETTING

print("\nSUBNETTING CALCULATION")

subnets = int(input("\nenter the number of required subnets: "))

if subnets <= 0:
    print("\ninvalid number of subnets")
    exit()

#find the min no of bits to borrow
#we need 2^borrowed_bits >= required subnets
borrowed_bits = 0

while power_of_two(borrowed_bits) < subnets:
    borrowed_bits += 1

prefix = default_prefix + borrowed_bits

if prefix > 30:
    print("\nCannot create", subnets, "subnets while keeping usable")
    print("host addresses in every subnet.")
    exit()

# rem bits are used for host addresses
host_bits = 32 - prefix

#new subnet mask
m1, m2, m3, m4 = get_subnet_mask(prefix)


total_subnets = power_of_two(borrowed_bits)
hosts_per_subnet = power_of_two(host_bits) - 2

print("\nOriginal Prefix        : /", default_prefix, sep="")
print("Required Subnets       :", subnets)
print("Borrowed Bits          :", borrowed_bits)
print("New Prefix             : /", prefix, sep="")

print("\nSubnet Mask            :", m1, m2, m3, m4, sep=".")
print("Number of Subnets      : 2^", borrowed_bits, " = ", total_subnets, sep="")
print("Host Bits per Subnet   :", host_bits)
print("Hosts per Subnet       : 2^", host_bits, " - 2 = ", hosts_per_subnet, sep="")



# CALCULATE NETWORK ADDRESS

# convert dotted decimal ip into a single 32bit int
ip = (a << 24) | (b << 16) | (c << 8) | d

# block size = total addresses in each subnet
block_size = power_of_two(host_bits)

# network address = ip round down to the nearest block boundary
network_address = ip - (ip % (2 ** (32 - default_prefix)))


print("\nSUBNET INFORMATION")
print("\nBlock Size :", block_size, "addresses")

for i in range(total_subnets):

    # each subnet starts after the previous subnet block size
    current_network = network_address + (i * block_size)

    # broadcast address is the last address in the subnet
    current_broadcast = current_network + block_size - 1

    first_host = current_network + 1
    last_host = current_broadcast - 1

    print("\n----------------------------------------------------")
    print("Subnet", i + 1)

    print("Network Address :", int_to_ip(current_network))
    print("First Host      :", int_to_ip(first_host))
    print("Last Host       :", int_to_ip(last_host))
    print("Broadcast       :", int_to_ip(current_broadcast))
