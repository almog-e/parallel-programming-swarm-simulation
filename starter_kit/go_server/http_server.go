// Simple Go HTTP server
// Build: go build -o http_server http_server.go
// Run:   ./http_server
// The server will listen on http://localhost:9001

package main

import (
	"context"
	"fmt"
	"log"
	"net/http"
	"os"
	"os/signal"
	"sync/atomic"
	"syscall"
	"time"
)

var receivedMessages []string
var shuttingDown int32

func main() {
	shutdownChan := make(chan struct{})
	server := &http.Server{Addr: ":9001"}

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "text/html; charset=utf-8")
		fmt.Fprintf(w, `
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>Go Message Server</title>
<style>
  body { font-family: 'Segoe UI', Arial, sans-serif; background: #181c24; color: #f8f8f2; margin: 0; padding: 0; }
  .container { max-width: 600px; margin: 40px auto; background: #232946; border-radius: 12px; box-shadow: 0 4px 24px #0008; padding: 32px; }
  h1 { color: #eebf6b; margin-top: 0; }
  ul { padding-left: 1.2em; }
  li { margin-bottom: 0.5em; }
  .form { margin-top: 2em; }
  input[type=text] { padding: 8px; border-radius: 6px; border: none; width: 70%; font-size: 1em; }
  button { padding: 8px 18px; border-radius: 6px; border: none; background: #eebf6b; color: #232946; font-weight: bold; font-size: 1em; cursor: pointer; transition: background 0.2s; }
  button:hover { background: #ffd580; }
  .empty { color: #aaa; }
  .shutdown { margin-top: 2em; background: #e74c3c; color: #fff; }
  .shutdown:hover { background: #ff6f61; }
</style>
</head>
<body>
<div class="container">
<h1>Go Message Server </h1>
`)
		if len(receivedMessages) == 0 {
			fmt.Fprintf(w, `<p class="empty">No messages received yet.</p>`)
		} else {
			fmt.Fprintf(w, `<ul>`)
			for _, msg := range receivedMessages {
				fmt.Fprintf(w, `<li>%s</li>`, msg)
			}
			fmt.Fprintf(w, `</ul>`)
		}
		fmt.Fprintf(w, `
<form class="form" method="POST" action="/send">
  <input type="text" name="msg" placeholder="Type a message..." autocomplete="off" required />
  <button type="submit">Send</button>
</form>
<form method="POST" action="/shutdown">
  <button class="shutdown" type="submit">Shutdown Server</button>
</form>
</div>
</body>
</html>`)
	})

	http.HandleFunc("/send", func(w http.ResponseWriter, r *http.Request) {
		if r.Method == "POST" {
			msg := r.FormValue("msg")
			if msg != "" {
				receivedMessages = append(receivedMessages, msg)
				fmt.Fprintf(w, "<p style='color: #eebf6b;'>Message received: %s</p><a href='/'>Back</a>", msg)
				return
			}
		}
		fmt.Fprintf(w, "<p>Send a message with POST and 'msg' field.</p><a href='/'>Back</a>")
	})

	http.HandleFunc("/shutdown", func(w http.ResponseWriter, r *http.Request) {
		if r.Method == "POST" && atomic.CompareAndSwapInt32(&shuttingDown, 0, 1) {
			fmt.Fprintf(w, "<p>Server is shutting down...</p>")
			go func() {
				shutdownChan <- struct{}{}
			}()
		} else {
			fmt.Fprintf(w, "<p>Shutdown already in progress.</p>")
		}
	})

	go func() {
		log.Println("HTTP server listening on :9001")
		if err := server.ListenAndServe(); err != nil && err != http.ErrServerClosed {
			log.Fatalf("ListenAndServe: %v", err)
		}
	}()

	// Wait for shutdown signal
	sigChan := make(chan os.Signal, 1)
	signal.Notify(sigChan, syscall.SIGINT, syscall.SIGTERM)
	select {
	case <-shutdownChan:
		log.Println("Shutdown requested from web UI.")
	case sig := <-sigChan:
		log.Printf("Received signal: %v", sig)
	}

	atomic.StoreInt32(&shuttingDown, 1)
	ctx, cancel := context.WithTimeout(context.Background(), 3*time.Second)
	defer cancel()
	if err := server.Shutdown(ctx); err != nil {
		log.Fatalf("Server Shutdown Failed:%+v", err)
	}
	log.Println("Server exited cleanly.")
}
