package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
)

func main() {
	listener, err := net.Listen("tcp", ":9000")
	if err != nil {
		log.Fatal(err)
	}
	defer listener.Close()
	log.Println("Go server listening on :9000")

	conn, err := listener.Accept()
	if err != nil {
		log.Fatal(err)
	}
	defer conn.Close()

	scanner := bufio.NewScanner(conn)
	for scanner.Scan() {
		line := scanner.Text()
		log.Printf("received: %s", line)
		fmt.Fprintf(conn, "ack %s\n", line)
	}

	if err := scanner.Err(); err != nil {
		log.Println("scanner error:", err)
	}
}
