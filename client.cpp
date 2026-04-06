#include <arpa/inet.h>  // inet_pton() - converts IP string to binary
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

int main() {
  // Step 1: Create a socket
  int client_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (client_fd == -1) {
    std::cerr << "Socket creation failed\n";
    return 1;
  }
  // Step 2: Define the server address to connect to
  sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(6767);

  // Convert IP address from text to binary
  // 127.0.0.1 is localhost (your own machine)
  if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
    std::cerr << "Invalid address\n";
    return 1;
  }

  // Step 3: Connect to the server
  if (connect(client_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    std::cerr << "Connection failed\n";
    return 1;
  }
  std::cout << "Connected to server!\n";

  // Step 4: Send a message
  std::string message = "Hello from client!";
  write(client_fd, message.c_str(), message.size());

  // Step 5: Receive the reply
  char buffer[1024] = {0};
  read(client_fd, buffer, sizeof(buffer));
  std::cout << "Server replied: " << buffer << "\n";

  // Step 6: Close
  close(client_fd);

  return 0;
}