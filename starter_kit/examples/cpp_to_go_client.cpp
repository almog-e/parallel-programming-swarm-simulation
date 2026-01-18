#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <string>

int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    std::cerr << "Failed to create socket.\n";
    return 1;
  }

  sockaddr_in server_addr{};
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(9000);
  if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
    std::cerr << "Invalid address.\n";
    close(sock);
    return 1;
  }

  if (connect(sock, reinterpret_cast<sockaddr *>(&server_addr), sizeof(server_addr)) != 0) {
    std::cerr << "Failed to connect.\n";
    close(sock);
    return 1;
  }

  for (int i = 1; i <= 5; ++i) {
    std::string message = std::to_string(i) + "\n";
    send(sock, message.c_str(), message.size(), 0);
  }

  close(sock);
  return 0;
}
