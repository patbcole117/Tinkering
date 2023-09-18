package main

import (
    "fmt"
    "io"
    "github.com/patbcole117/Tinkering/Go/transport/comms"
)

func main() {
    rx := comms.NewHTTPCommRx("127.0.0.1", 8888)
    if err := rx.StartSrv(); err != nil {
        panic(err)
    }

    if err := rx.StopSrv(); err != nil {
        panic(err)
    }    

    if err := rx.StartSrv(); err != nil {
        panic(err)
    }

    tx := comms.NewHTTPCommTx()
    res, err := tx.Get("http://127.0.0.1:8888")
    if err != nil {
        panic(err)
    }

    msg, err := io.ReadAll(res.Body)    
    if err != nil {
        panic(err)
    }
    fmt.Println("Echo: " + string(msg))

    m :=  map[string]interface{} {
        "Color": "Blue",
        "Manufacturer": "Toyota",
        "Model":    "Tundra",
        "Speed":    70,
    }
    
    res, err = tx.SendJson(m, "http://127.0.0.1:8888/")
    if err != nil {
        panic(err)
    }    

    msg, err = io.ReadAll(res.Body)    
    if err != nil {
        panic(err)
    }
    fmt.Println("Echo: " + string(msg))
    
}
