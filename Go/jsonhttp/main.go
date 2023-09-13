package main

import (
    "bytes"
    "fmt"
    "io"
    "encoding/json"
    "net/http"
    
    "github.com/go-chi/chi/v5"
    "github.com/patbcole117/Tinkering/Go/jsonhttp/node"
)

func main() {
    r := chi.NewRouter()
    r.Get("/", Check)    
    r.Post("/Node", CreateNode)    
    http.ListenAndServe("127.0.0.1:8080", r)
}

func CreateNode(w http.ResponseWriter, r *http.Request) {
    body, err := io.ReadAll(r.Body)
    if err != nil {
        panic(err)
    }
    res := fmt.Sprintf(`{"body": "%s"}%s`, body, "\n")
    w.Write([]byte(res))
    
    var umNode node.Node
    err = json.Unmarshal(body, &umNode)
    if err != nil {
        panic(err)
    }
    umNode.SrvStart()
    fmt.Printf(`{"umNode": "%v"}%s`, umNode, "\n")
    fmt.Printf(`{"umNode": "%+v"}%s`, umNode, "\n")
    
    mNode, err := json.Marshal(umNode)
    if err != nil {
        panic(err)
    } 
    res = fmt.Sprintf(`{"mNode": "%s"}%s`, mNode, "\n")
    w.Write([]byte(res))

    var dNode node.Node
    rNode := bytes.NewReader(body)
    jd := json.NewDecoder(rNode)
    err = jd.Decode(&dNode)  
    if err != nil {
        panic(err)
    }
    fmt.Printf(`{"dNode": "%v"}%s`, dNode, "\n")
    fmt.Printf(`{"dNode": "%+v"}%s`, dNode, "\n")
    
    je := json.NewEncoder(w)
    err = je.Encode(dNode)
    if err != nil {
        panic(err)
    } 
}

func Check(w http.ResponseWriter, r *http.Request) {
    resp := fmt.Sprintf(`{"Msg": "Hello!"}%s`, "\n")
    w.Write([]byte(resp))
}
