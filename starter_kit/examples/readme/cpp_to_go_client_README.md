# C++ to Go Client Example

This example sends numbers 1..5 to a Go TCP server.

## Build

```bash
g++ cpp_to_go_client.cpp -o cpp_to_go_client
```

## Run

Start the Go server first (see go_server_README.md), then run:
```bash
./cpp_to_go_client
```

## Requirements
- C++ compiler (g++)
- Go server running on localhost:9000
