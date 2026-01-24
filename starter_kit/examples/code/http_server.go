package main

import (
	"fmt"
	"log"
	"net/http"
)

var receivedMessages []string

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintf(w, "<h1>Received Messages</h1>")
		if len(receivedMessages) == 0 {
			fmt.Fprintf(w, "<p>No messages received yet.</p>")
		} else {
			fmt.Fprintf(w, "<ul>")
			for _, msg := range receivedMessages {
				fmt.Fprintf(w, "<li>%s</li>", msg)
			}
			fmt.Fprintf(w, "</ul>")
		}
	})

	http.HandleFunc("/send", func(w http.ResponseWriter, r *http.Request) {
		if r.Method == "POST" {
			msg := r.FormValue("msg")
			if msg != "" {
				receivedMessages = append(receivedMessages, msg)
				fmt.Fprintf(w, "Message received: %s", msg)
				return
			}
		}
		fmt.Fprintf(w, "Send a message with POST and 'msg' field.")
	})

	log.Println("HTTP server listening on :9001")
	log.Fatal(http.ListenAndServe(":9001", nil))
}
