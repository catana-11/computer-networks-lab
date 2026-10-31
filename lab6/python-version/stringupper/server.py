import socket

# Create UDP socket
server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind server to IP and port
server.bind(("127.0.0.1", 12345))

print("Server is waiting for messages...")

# Receive message from client
message, addr = server.recvfrom(1024)

# Decode received message
text = message.decode()

print("Received from client:", text)

# Convert lowercase to uppercase
uppercase_text = text.upper()

# Send converted string back to client
server.sendto(uppercase_text.encode(), addr)

print("Converted string:", uppercase_text)

# Close server socket
server.close()