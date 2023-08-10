package main

import(
    "fmt"
)

func main(){
    aString := "Hello World!"
    fmt.Println("First Character:", aString[0])
    fmt.Println("First Character:", string(aString[0]))

    r := 'H'
    
    fmt.Println("int32:", r)
    fmt.Printf("string: %s\n", r)
    fmt.Printf("character: %c\n", r)

    for _, v := range aString{
        fmt.Printf("%x ", v)
    }
    fmt.Println()
    
    for _, v := range aString{
        fmt.Printf("%c ", v)
    }
    fmt.Println()
}
