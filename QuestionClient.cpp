#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

int main() {
  // Creating a socket
  int client = socket(AF_INET, SOCK_STREAM, 0);
  if (client == -1) {
    std::cerr << "Socket creation failed\n";
    return 1;
  }

  // There's a inbuilt struct sockaddr_in which we use to specify the
  // configurations of the socket in sys/socket.h
  sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8080);

  if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
    std::cerr << "Invalid address\n";
    return 1;
  }

  //  Connecting to server
  if (connect(client, (sockaddr*)&server_address, sizeof(server_address)) ==
      -1) {
    std::cerr << "Connection failed\n";
    return 1;
  }
  std::cout << "Connected to server!\n";

  //  Sending a message
  std::string message = "Hello Server";
  write(client, message.c_str(), message.size());
  std::cout << "Message sent: " << message << "\n";

  close(client);
  return 0;
}