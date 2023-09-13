package notmain

import (
    "bytes"
    "fmt"
    "io"
    "encoding/json"
    "os"
    "net/http"
    //"strings"
    "time"
    
    "github.com/go-chi/chi/v5"
)

type Book struct {
    Author  string
    Title   string
    Dop     time.Time
}

func (b *Book) UnmarshalJSON(j []byte) error {
    type Alias Book
    aux := &struct{
        Dop string   `json:"dop"`
        *Alias
    }{
        Alias:  (*Alias)(b),
    }

    if err := json.Unmarshal(j, &aux); err != nil {
        return err
    }
   
    t, err := time.Parse(time.DateOnly, aux.Dop)
    b.Dop = t
    if err != nil {
        return err
    }
    return nil
}

func (b *Book) MarshalJSON() ([]byte, error) {
    type Alias Book
    return json.Marshal(&struct {
        Dop string  `json:"dop"`
        *Alias
    }{
        Dop: b.Dop.Format(time.DateOnly),
        Alias:  (*Alias)(b),
    })
}
/*
func main() {
    r := chi.NewRouter()
    r.Get("/", Check)    
    r.Post("/book", CreateBook)    
    http.ListenAndServe("127.0.0.1:8080", r)
}
*/
func CreateBook(w http.ResponseWriter, r *http.Request) {
    body, err := io.ReadAll(r.Body)
    if err != nil {
        panic(err)
    }
    res := fmt.Sprintf(`{"body": "%s"}%s`, body, "\n")
    w.Write([]byte(res))
    
    var umBook Book
    err = json.Unmarshal(body, &umBook)
    if err != nil {
        panic(err)
    }
    
    fmt.Printf(`{"umBook": "%v"}%s`, umBook, "\n")
    fmt.Printf(`{"umBook": "%+v"}%s`, umBook, "\n")
    
    mBook, err := json.Marshal(umBook)
    if err != nil {
        panic(err)
    } 
    res = fmt.Sprintf(`{"mBook": "%s"}%s`, mBook, "\n")
    w.Write([]byte(res))

    var dBook Book
    rBook := bytes.NewReader(body)
    jd := json.NewDecoder(rBook)
    err = jd.Decode(&dBook)  
    if err != nil {
        panic(err)
    }
    fmt.Printf(`{"dBook": "%v"}%s`, dBook, "\n")
    fmt.Printf(`{"dBook": "%+v"}%s`, dBook, "\n")
    
    je := json.NewEncoder(w)
    err = je.Encode(dBook)
    if err != nil {
        panic(err)
    } 
}

func Check(w http.ResponseWriter, r *http.Request) {
    resp := fmt.Sprintf(`{"Msg": "Hello!"}%s`, "\n")
    w.Write([]byte(resp))
}

func bookTest() {
    book := Book{Author: "Pat", Title: "The Book", Dop: time.Now()}
    fmt.Printf("book: %v\n", book)
    fmt.Printf("book: %+v\n", book)
    fmt.Println()
    
    mBook, err := json.Marshal(book)
    if err != nil {
        panic(err)
    }
    fmt.Printf("mBook: %s\n", string(mBook))
    fmt.Println()

    var umBook Book
    err = json.Unmarshal(mBook, &umBook)
    if err != nil {
        panic(err)
    }    
    fmt.Printf("umBook: %v\n", umBook)
    fmt.Printf("umBook: %+v\n", umBook)
    fmt.Println()

    var dBook Book
    rBook := bytes.NewReader(mBook)
    jd := json.NewDecoder(rBook)
    err = jd.Decode(&dBook)
    if err != nil {
        panic(err)
    }   
    fmt.Printf("dBook: %v\n", dBook)
    fmt.Printf("dBook: %+v\n", dBook)
    fmt.Println()
    
    je := json.NewEncoder(os.Stdout)
    err = je.Encode(dBook)
    if err != nil {
        panic(err)
    }
}

