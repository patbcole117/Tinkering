package node

import (
	"encoding/json"
	"fmt"
	"io"
	"log"
	"math/rand"
	"net/http"
	"strconv"
	"time"
)

const (
	ERROR    	= -1
	STOPPED     = 0
	LISTENING   = 1

	SERVER_DEFAULT_IP      		string        	= "127.0.0.1"
	SERVER_DEFAULT_PORT    		int           	= 80
	SERVER_DEFAULT_TIMEOUT 		time.Duration 	= 3 * time.Second
	SERVER_DEFAULT_NAME_SIZE 	int 			= 10
)
//curl http://127.0.0.1:8080/Node -d '{"name":"Bob", "ip":"127.0.0.1", "port":8888, "status":1, "dob":"2022-09-09", "hello":"2199-05-02"}'
type Node struct {
	Id  	string		`json:"_id,omitempty"`
	Name   	string		`json:"name"`
	Ip     	string   	`json:"ip"`
	Port   	int      	`json:"port"`
	Status 	int      	`json:"status"`
    Dob     time.Time	`json:"dob"`
	Hello 	time.Time	`json:"hello"`
	server 	*http.Server    `json:"server,omitempty"`
}

func NewNode() Node {
	n := Node {
	Ip:		SERVER_DEFAULT_IP,
	Port:	SERVER_DEFAULT_PORT,
	}
    n.Dob = time.Now()
	n.initName(SERVER_DEFAULT_NAME_SIZE)
	return n
}

func (n *Node) initName(sz int) {
	abc := []rune("abcdefghijklmnopqrstuvwxyz1234567890")
	b := make([]rune, sz)
	for i := range b {
		b[i] = abc[rand.Intn(len(abc))]
	}
	n.Name = string(b)
}

func (n *Node) SrvStart() error {
	addy := n.Ip + ":" + strconv.Itoa(n.Port)
	m := http.NewServeMux()
	s := http.Server{
		Addr:         addy,
		Handler:      m,
		ReadTimeout:  SERVER_DEFAULT_TIMEOUT,
		WriteTimeout: SERVER_DEFAULT_TIMEOUT,
	}
	m.HandleFunc("/", n.urlRoot)
	m.HandleFunc("/info", n.urlInfo)

	n.server = &s

	go s.ListenAndServe()

	//TODO: Test for correct name. If wrong name, ip is taken. If no response, failure.
	time.Sleep(SERVER_DEFAULT_TIMEOUT)

	n.Status = LISTENING
	return nil
}

func (n *Node) SrvStop() error {
	err := n.server.Close()
	time.Sleep(SERVER_DEFAULT_TIMEOUT)
	n.Status = STOPPED
	return err
}

func (n *Node) UnmarshalJSON(j []byte) error {
    type Alias Node
    aux := &struct{
        Dob 	string	`json:"dob"`
		Hello 	string	`json:"hello"`	
        *Alias
    }{
        Alias:  (*Alias)(n),
    }

    if err := json.Unmarshal(j, &aux); err != nil {
        return err
    }
   
    t, err := time.Parse(time.DateOnly, aux.Dob)
    if err != nil {
        return err
    }
	n.Dob = t
    
	t, err = time.Parse(time.DateOnly, aux.Hello)
    if err != nil {
        return err
    }
	n.Hello = t
    return nil
}

func (n *Node) MarshalJSON() ([]byte, error) {
    type Alias Node
    return json.Marshal(&struct {
        Dob 	string  `json:"dob"`
		Hello 	string  `json:"hello"`
        *Alias
    }{
        Dob: 	n.Dob.Format(time.DateOnly),
		Hello: 	n.Hello.Format(time.DateOnly),
        Alias:  (*Alias)(n),
    })
}

func (n *Node) ToJsonPretty() (string) {
	b, err := json.MarshalIndent(n, "", "    ")
	if err != nil {
		return string(make([]byte, 0))
	}
	return string(b)
}

func (n *Node) urlRoot(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Date", time.Now().Format(time.UnixDate))
	msg := fmt.Sprintf("[+] Hello from %s.\n", n.Name)
	io.WriteString(w, msg)
}

func (n *Node) urlInfo(w http.ResponseWriter, r *http.Request) {
    w.Header().Set("Date", time.Now().Format(time.UnixDate))
    b, err:= json.Marshal(n)
	if err != nil {
		log.Print(err)
	}
	msg := string(b)
    io.WriteString(w, msg)
}
