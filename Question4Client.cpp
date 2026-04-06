#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

int main() {
  int client = socket(AF_INET, SOCK_STREAM, 0);
  if (client == -1) {
    std::cerr << "Socket creation failed\n";
    return 1;
  }

  sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(6767);

  if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
    std::cerr << "Invalid address\n";
    return 1;
  }

  if (connect(client, (sockaddr*)&server_address, sizeof(server_address)) ==
      -1) {
    std::cerr << "Connection failed\n";
    return 1;
  }
  std::cout << "Connected to server!\n";

  std::string message = "Hello from client!";
  write(client, message.c_str(), message.size());

  char buffer[1024] = {0};
  read(client, buffer, sizeof(buffer));
  std::cout << "Server replied: " << buffer << "\n";

  // Step 6: Close
  close(client);

  return 0;
}
