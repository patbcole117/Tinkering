package main
import "fmt"

func main(){
    // Classic C-style for-loop in Go.
    for i:= 0; i < 10; i++ {
        fmt.Print(i*i, " ")
    }
    fmt.Println()
    
    // Idiomatic Go for-loop.
    j := 0
    for ok := true; ok; ok=(j != 10){
        fmt.Print(j*j, " ")
        j++
    }
    fmt.Println()

    // While loop in Go.
    k:= 0
    for {
        if k == 10{
            break
        }
        fmt.Print(k*k, " ")
        k++
    }
    fmt.Println()

    // Range allows iteration over collections.
    aSlice := []int{-1, 2, 1, -1, 2, -2}
    for x, y := range aSlice{
        fmt.Println("index:", x, "value:", y)
    }
}
