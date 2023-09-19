package main

import (
    "fmt"
    "io"
    "github.com/patbcole117/Tinkering/Go/transport/comms"
    "github.com/patbcole117/Tinkering/Go/transport/agent"
)

func main() {
    rx := comms.NewHTTPCommRX("127.0.0.1", 8888)
    if err := rx.StartSrv(); err != nil {
        panic(err)
    }
    a, _ := agent.NewAgent("Bob", "http://127.0.0.1:8888/", "http")
    a.Run()
}

func TestRestart() {
    rx := comms.NewHTTPCommRX("127.0.0.1", 8888)
    if err := rx.StartSrv(); err != nil {
        panic(err)
    }

    if err := rx.StopSrv(); err != nil {
        panic(err)
    }    

    if err := rx.StartSrv(); err != nil {
        panic(err)
    }

    tx := comms.NewHTTPCommTX()
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
    
    res, err = tx.SendJSON(m, "http://127.0.0.1:8888/")
    if err != nil {
        panic(err)
    }    

    msg, err = io.ReadAll(res.Body)    
    if err != nil {
        panic(err)
    }
    fmt.Println("Echo: " + string(msg))
    
}
