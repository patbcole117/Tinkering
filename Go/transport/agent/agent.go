package agent

import (
    "encoding/json"
    "io"
    "time"
    "github.com/patbcole117/Tinkering/Go/transport/comms"
)

var (
    AGENT_CHANNEL_LIMIT int = 10
    AGENT_SLEEP_TIME time.Duration = 3 * time.Second
)

type Agent struct {
    Name    string
    Home    string
    OutQ    chan Msg
    InQ     chan Msg
    Tx      comms.CommsPackage
}

type Msg struct {
    From    string
    Type    string
    Ref     string
    Content string
}

func NewAgent(n, h, c string) (*Agent, error) {
    a := &Agent {
        Name:   n,
        Home:   h,
        OutQ:   make(chan Msg, AGENT_CHANNEL_LIMIT),
        InQ:    make(chan Msg, AGENT_CHANNEL_LIMIT),
    }
    
    tx, err := comms.NewCommsPackage(c)
    if err != nil {
        return nil, err
    }
    a.Tx = tx

    return a, nil
}

func (a *Agent) Run() {
    for i := 1; i < 5; i++ {
        a.SayHello()
        a.DoNext()
        time.Sleep(AGENT_SLEEP_TIME)
    }
}

func(a *Agent) SayHello() {
    var m Msg

    select {
    case m = <-a.OutQ:
    default:
        m = Msg{From: a.Name, Type: "nop", Ref: "",  Content: ""}
    }

    res, err := a.Tx.SendJSON(m, a.Home)
    if err != nil {
        m = Msg{From: a.Name, Type: "err", Ref: "nil",  Content: err.Error()}
        a.OutQ <-m
        return
    }
    
    body, err := io.ReadAll(res.Body)
    if err != nil {
        m = Msg{From: a.Name, Type: "err", Ref: "nil",  Content: err.Error()}
        a.OutQ <-m
        return
    }

    if err = json.Unmarshal(body, &m); err != nil {
        m = Msg{From: a.Name, Type: "err", Ref: "nil",  Content: err.Error()}
        a.OutQ <-m
        return
    }
    
    if m.Type == "job" {
        a.InQ <-m
    }
}

func (a *Agent) DoNext() {
    m := <-a.InQ
    // Do the thing
    // TODO = result
    a.OutQ <-Msg{From: a.Name, Type: "result", Ref: m.Ref, Content: "TODO"}
}
