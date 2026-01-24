# Go HTTP Server Example

This example provides a simple HTTP server that displays received messages and allows you to send new messages via a web page or HTTP POST.

## How to Run

1. Open a terminal and navigate to the go_server directory:
   ```bash
   cd go_server
   ```
2. Start the HTTP server:
   ```bash
   go run http_server.go
   ```
3. Open your browser and go to:
   - http://localhost:9001
     - View all received messages.
   - http://localhost:9001/send
     - Send a message using an HTTP POST with the field `msg`.

## How to Send a Message

You can send a message using curl:
```bash
curl -X POST -d "msg=Hello from curl!" http://localhost:9001/send
```

## Features
- Displays all received messages on the main page.
- Accepts new messages via HTTP POST to `/send`.

## Requirements
- Go (https://golang.org/dl/)
- Web browser or curl

---
You can customize the server to connect with other parts of your project if needed.
