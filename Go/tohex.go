package main

import(
    "fmt"
    "strconv"
    "os"
)

func main(){
    args := os.Args
    if len(args) != 2{
        fmt.Println("[?] usage:", args[0], "[0 - 18446744073709551615]")
        return
    }

    num_dec, err := strconv.ParseUint(args[1], 10, 64) 
    if err != nil{
        fmt.Println("[-]", err)
        return
    }

    num_hex := strconv.FormatUint(num_dec, 16)
    fmt.Println(num_hex)
}
