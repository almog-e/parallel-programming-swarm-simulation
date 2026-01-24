# C++ to Go HTTP Client Example

This example demonstrates how to send HTTP POST requests from a C++ client to the Go HTTP server at /send, posting numbers 1 to 5 as messages.

## How to Build

```bash
g++ cpp_to_go_http_client.cpp -o cpp_to_go_http_client
```

## How to Run

1. Start the Go HTTP server (http_server.go) on port 9001:
   ```bash
   cd go_server
   go run http_server.go
   ```
2. In another terminal, run the C++ HTTP client:
   ```bash
   ./cpp_to_go_http_client
   ```

## What It Does
- Sends 5 HTTP POST requests to http://localhost:9001/send with messages "msg=1" to "msg=5".
- Prints the server's response for each message.

## Requirements
- C++ compiler (g++)
- Go HTTP server running on port 9001

---
You can modify the client to send other messages or interact with different endpoints as needed.
