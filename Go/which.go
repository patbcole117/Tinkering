package main
import(
    "fmt"
    "os"
    "path/filepath"
)

func main(){
    args := os.Args
    if len(args) != 2{
        fmt.Println("usage:", args[0], "<binary>")
        return
    }

    file := args[1]
    path := os.Getenv("PATH")
    pathSplit := filepath.SplitList(path)
    for _, dir := range pathSplit {
        fullPath := filepath.Join(dir, file)
        fileInfo, err := os.Stat(fullPath)
        if err == nil{
            mode := fileInfo.Mode()
            if mode.IsRegular(){
                if mode&0111 != 0{
                    fmt.Println(fullPath)
                    return
                }
            }
        }
    }
}
