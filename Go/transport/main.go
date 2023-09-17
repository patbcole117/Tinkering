package main

import (
	"fmt"
	"time"
)

func print(s string){
	fmt.Println(s)
}

func main() {
	a := []string{"one", "two", "three", "four", "five"}

	for i := range a {
		go print(a[i])
	}
	time.Sleep( 1 * time.Second)
}
