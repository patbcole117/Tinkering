package main
import (
    "fmt"
    "os"
    "strconv"
)

func main(){
    args := os.Args
    if len(args) < 2{
        fmt.Println("Need one or more arguemnts.")
        return
    }

    var min, max float64
    for i := 1; i < len(args); i++ {
        n, err := strconv.ParseFloat(args[i], 64)
        if err != nil{
            continue
        }

        if i == 1{
            min = n
            max = n
            continue
        }

        if n < min{
            min = n
        }
        if n > max{
            max = n
        }
    }
        fmt.Println("Min: ", min)
        fmt.Println("Max: ", max)
}
