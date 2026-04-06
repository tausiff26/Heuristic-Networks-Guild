#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

int main() {
  // Creating a socket here.
  int server = socket(AF_INET, SOCK_STREAM, 0);
  //   server contains an integer basically a name for this particular socket
  //   whatever
  //  we wish to achieve using this socket will be done using this integer.
  //  The arguments are basically domain,type and protocol here for 0 it means
  //  that it will use
  // the default protocol which is TCP for SOCK_STREAM+AF_INET
  if (server == -1) {
    std::cerr << "Socket creation failed\n";
    return 0;
  }
  std::cout << "Socket creation\n";
  //   We are defining the server address here.
  sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(8080);  // port name 6767
  // Now we will bind the socket to an address and port
  bind(server, (sockaddr*)&server_address, sizeof(server_address));
  listen(server, 1);

  sockaddr_in client_address;
  socklen_t client_len = sizeof(client_address);
  int client = accept(server, (sockaddr*)&client_address, &client_len);

  char buffer[1024] = {0};
  read(client, buffer, sizeof(buffer));

  std::string reply = "Hello";
  write(client, reply.c_str(), reply.size());

  close(client);
  close(server);
}
