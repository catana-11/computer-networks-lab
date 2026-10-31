import socket

# Create UDP socket
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Take string input from user
message = input("Enter a lowercase string: ")

# Send message to server
client.sendto(message.encode(), ("127.0.0.1", 12345))

# Receive converted string from server
data, addr = client.recvfrom(1024)

# Display uppercase string
print("Uppercase string received from server:", data.decode())

# Close client socket
client.close()