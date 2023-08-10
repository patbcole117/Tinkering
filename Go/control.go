package main
import(
    "fmt"
    "os"
    "strconv"
)

func main(){
    if len(os.Args) != 2{
        fmt.Println("Please provide a command line argument.")
        return
    }
    argument := os.Args[1]

    switch argument{
    case "0":
        fmt.Println("Zero!")
    case "1":
        fmt.Println("One!")
    case "2":
        fmt.Println("Two!")
        fallthrough
    default:
        fmt.Println("Value:", argument)
    }

    value, err := strconv.Atoi(argument)
    if err != nil{
        fmt.Println("Cannot convert to int:", argument)
        return
    }

    switch{
    case value == 0:
        fmt.Println("Zero!")
    case value > 0:
        fmt.Println("Positive Integer!")
    case value < 0:
        fmt.Println("Negative Integer!")
    default:
        fmt.Println("This should never happen.")
    }
}
