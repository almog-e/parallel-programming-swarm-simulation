// Simple C++ HTTP client for Go server
// Build: g++ -o cpp_to_go_http_client cpp_to_go_http_client.cpp
// Run:   ./cpp_to_go_http_client
// NOTE: The Go server must be running on 127.0.0.1:9001 before running this client.

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>

int main() {
    for (int i = 1; i <= 5; ++i) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            std::cerr << "Failed to create socket.\n";
            return 1;
        }

        sockaddr_in server_addr{};
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(9001);
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

        std::string body = "msg=" + std::to_string(i);
        std::ostringstream oss;
        oss << "POST /send HTTP/1.1\r\n"
            << "Host: 127.0.0.1:9001\r\n"
            << "Content-Type: application/x-www-form-urlencoded\r\n"
            << "Content-Length: " << body.size() << "\r\n"
            << "Connection: close\r\n"
            << "\r\n"
            << body;
        std::string request = oss.str();
        send(sock, request.c_str(), request.size(), 0);

        // Optionally, read and print the response
        char buffer[4096];
        ssize_t received = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (received > 0) {
            buffer[received] = '\0';
            std::cout << "Response for msg=" << i << ":\n"
                      << buffer << std::endl;
        }

        close(sock);
    }
    return 0;
}
