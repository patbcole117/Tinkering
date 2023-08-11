package main

import "fmt"

func main(){
    fmt.Printf("Please enter yor name: ")
    var name string
    fmt.Scanln(&name)
    fmt.Println("Your name is: ", name)
}
