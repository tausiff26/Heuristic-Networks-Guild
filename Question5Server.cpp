#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

int main() {
  int server = socket(AF_INET, SOCK_STREAM, 0);
  if (server == -1) {
    std::cerr << "Socket creation failed\n";
    return 1;
  }
  std::cout << "Socket created\n";

  sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(8080);

  bind(server, (sockaddr*)&server_address, sizeof(server_address));
  // binding the server to this address
  listen(server, 1);
  std::cout << "Port 8080\n";

  sockaddr_in client_address;
  socklen_t client_len = sizeof(client_address);
  int client_fd = accept(server, (sockaddr*)&client_address, &client_len);

  char buffer[1024] = {0};
  read(client_fd, buffer, sizeof(buffer));
  std::cout << "Message received: " << buffer << "\n";

  close(client_fd);
  close(server);
  return 0;
}