"""
An organization wants to divide the 
network 192.168.1.0/24 into two 
subnets. Write a program
in Python to calculate the 
subnet mask and the number of 
usable host addresses for
each subnet.
"""


ip = "192.168.1.0"
default_prefix = 24
required_subnets = 2

# Calculate borrowed bits
borrowed_bits = 0

while 2 ** borrowed_bits < required_subnets:
    borrowed_bits += 1

# Calculate new prefix
prefix = default_prefix + borrowed_bits

# Calculate remaining host bits
host_bits = 32 - prefix

# Calculate subnet mask
mask = (0xFFFFFFFF << (32 - prefix)) & 0xFFFFFFFF

m1 = (mask >> 24) & 255
m2 = (mask >> 16) & 255
m3 = (mask >> 8) & 255
m4 = mask & 255

# Calculate number of subnets and usable hosts
total_subnets = 2 ** borrowed_bits
hosts_per_subnet = (2 ** host_bits) - 2
block_size = 2 ** host_bits

print("\nOriginal Network:", ip, "/", default_prefix)
print("Required Subnets:", required_subnets)
print("Borrowed Bits:", borrowed_bits)
print("New Prefix: /", prefix, sep="")
print("Subnet Mask:", f"{m1}.{m2}.{m3}.{m4}")
print("Total Subnets:", total_subnets)
print("Usable Hosts per Subnet:", hosts_per_subnet)

# Convert IP address into integer
a, b, c, d = map(int, ip.split("."))
network = (a << 24) | (b << 16) | (c << 8) | d

# Display details of each subnet
print("\nSUBNET INFORMATION")

for i in range(total_subnets):
    current_network = network + (i * block_size)
    broadcast = current_network + block_size - 1

    first_host = current_network + 1
    last_host = broadcast - 1

    def int_to_ip(address):
        return ".".join(str((address >> shift) & 255)
                        for shift in (24, 16, 8, 0))

    print("\nSubnet", i + 1)
    print("Network Address:", int_to_ip(current_network))
    print("Subnet Mask:", f"{m1}.{m2}.{m3}.{m4}")
    print("First Host:", int_to_ip(first_host))
    print("Last Host:", int_to_ip(last_host))
    print("Broadcast Address:", int_to_ip(broadcast))
    print("Usable Hosts:", hosts_per_subnet)