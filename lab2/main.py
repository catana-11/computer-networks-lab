# hamming code (7,4)

h = ['_'] * 7
print(h)

data = input("enter 4 data bits (msb to lsb): ")

h[6], h[5], h[4], h[2] = map(int, data)
print(h[::-1])

#using even parity
h[0] = (h[2] + h[4] + h[6]) % 2
h[1] = (h[2] + h[5] + h[6]) % 2
h[3] = (h[4] + h[5] + h[6]) % 2

print("after calc parity bits: ", h[::-1])

print("\nhamming code: ", h[::-1])

received = input("\nenter received hamming code (msb to lsb): ")
h = list(map(int, received[::-1]))

# syndrome bits
s1 = (h[0] + h[2] + h[4] + h[6]) % 2
s2 = (h[1] + h[2] + h[5] + h[6]) % 2
s4 = (h[3] + h[4] + h[5] + h[6]) % 2

error_pos = s1 + (2 * s2) + (4 * s4)

if error_pos == 0:
    print("\nno error detected.")
else:
    print(f"\nerror detected at bit position {error_pos}")

    h[error_pos - 1] ^= 1

    print("corrected hamming code:", h[::-1])

print("\nrecovered data bits:", h[6], h[5], h[4], h[2], sep="")