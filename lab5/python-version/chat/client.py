import socket

# Create TCP socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to server
client.connect(("127.0.0.1", 12345))

print("Connected to server.")

# Keep chatting until either side types exit
while True:

    # Take message from user
    message = input("Client: ")

    # Send message to server
    client.sendall(message.encode())

    if message.lower() == "exit":
        break

    # Receive reply from server
    reply = client.recv(1024).decode()

    if not reply or reply.lower() == "exit":
        print("Server ended the chat.")
        break

    print("Server:", reply)

# Close connection
client.close()

print("Chat ended.")