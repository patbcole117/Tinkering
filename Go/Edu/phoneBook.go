package main
import(
    "fmt"
    "os"
)

type Entry struct{
    Name    string
    Surname string
    Tel     string
}
var data = []Entry{}

func search(query string) *Entry{
    for i, v := range data{
        if v.Surname == query{
            return &data[i]
        }
    }
    return nil
}

func list(){
    for _, v := range data{
        fmt.Println(v)
    }
}

func main(){
    args := os.Args
    if len(args) == 1{
        fmt.Println("[?] usage:", args[0], "[search | list] <arguments>")
        return
    }

    data = append(data, Entry{"Bob", "Johnson", "2822982899"})
    data = append(data, Entry{"John", "Veranda", "3833983899"})
    data = append(data, Entry{"Jacob", "Wendel", "2822985433"})

    switch args[1]{
    case "search":
        if len(args) != 3{
            fmt.Println("[?] usage:", args[0], "search <Surname>")
            return
        }
        res := search(args[2])
        if res == nil{
            fmt.Println("[-]", args[2], "does not exist.")
            return
        }
        fmt.Println(*res)
    case "list":
        list()
    default:
        fmt.Println("[-] Invalid args.")
    }
}
