package main

import (
	"fmt"
	"io"
	"os"
	"strconv"
)

var args = os.Args

func main() {

	if len(args) != 3 && len(args) != 4 {
		usage()
		return
	}

	switch args[1] {
	case "-r":
		readBytes(args[2])
	case "-w":
		writeBytes(args[2], args[3])
	default:
		usage()
	}
}

func writeBytes(bString string, fname string) {
	s, err := strconv.Unquote(`"` + bString + `"`)
	if err != nil {
		panic(err)
	}

	f, err := os.Create(fname)
	if err != nil {
		panic(err)
	}
	defer f.Close()

	n, err := f.WriteString(s)
	if err != nil {
		panic(err)
	}
	fmt.Printf("[+] Wrote %d bytes to %s.\n", n, fname)
}

func readBytes(fname string) {
	buffer := make([]byte, 1024)

	f, err := os.Open(fname)
	if err != nil {
		panic(err)
	}
	defer f.Close()

	n, err := f.Read(buffer)
	if err == io.EOF {
		return
	}
	if err != nil {
		panic(err)
	}

	fmt.Print(string(buffer[0:n]))
	fmt.Println()
}

func usage() {
	fmt.Println("Usage:")
	fmt.Println(args[0], "-r <filename>")
	fmt.Println(args[0], "-w <bytes> <filename>")
}
