package main

import(
    "fmt"
    "os"
    "strconv"
)

func main(){
    var total, numInts, numFloats int
    invalid := make([]string, 0)
    for _, k := range os.Args[1:]{
        _, err := strconv.Atoi(k)
        if err == nil{
            total++
            numInts++
            continue
        }
        
        _, err = strconv.ParseFloat(k, 64)
        if err == nil{
            total++
            numFloats++
            continue
        }

        invalid = append(invalid, k)
    }
    fmt.Println("Total:", total, "Ints:", numInts, "Floats:", numFloats)
}
