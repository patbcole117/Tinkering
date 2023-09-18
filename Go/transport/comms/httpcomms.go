package comms

import (
    "bytes"
    "encoding/json"
    "errors" 
    "fmt"
    "io"
	"net/http"
    "strconv"
    "time"
)

var (
    CONN_TIMEOUT time.Duration = 10 * time.Second
    SERVER_DELAY = 2 * time.Second
    USER_AGENT string = "Mozilla/5.0 (Android 4.4; Mobile; rv:41.0) Geko/41.0 Firefox/41.0"
)

type HTTPCommTx struct {
	C *http.Client
}

func NewHTTPCommTx() *HTTPCommTx{
    return &HTTPCommTx{C: &http.Client{Timeout: CONN_TIMEOUT}}
}

func (tx *HTTPCommTx) SendJson(msg interface{}, dst string)(*http.Response, error) {
    b, err := json.Marshal(msg)
    if err != nil {
        return nil, err
    } 
    body := bytes.NewReader(b)

    req, err := http.NewRequest(http.MethodPost, dst, body)
    if err != nil {
        return nil, err
    }

    req.Header.Set("Content-Type", "application/json")
    req.Header.Set("User-Agent", USER_AGENT)
    req.Header.Set("Date", time.Now().Format(time.RFC1123))
    
    res, err := tx.C.Do(req)
    if err != nil {
        return nil, err
    }
    return res, nil
}

func (tx *HTTPCommTx) Get(dst string) (*http.Response, error) {
    req, err := http.NewRequest(http.MethodGet, dst, nil)
    if err != nil {
        return nil, err
    }

    req.Header.Set("User-Agent", USER_AGENT)
    req.Header.Set("Date", time.Now().Format(time.RFC1123))
    
    res, err := tx.C.Do(req)
    if err != nil {
        return nil, err
    }
    return res, nil
}

var ErrNilSrv = errors.New("server is nil")
type HTTPCommRx struct {
    Ip      string
    Port    int
    Srv       *http.Server
}
func NewHTTPCommRx(i string, p int) *HTTPCommRx {
    rx := HTTPCommRx{Ip: i, Port: p}
    srv := rx.ProvisionSrv()
    rx.Srv = srv
    return &rx
}

func (rx *HTTPCommRx) StartSrv() error {
    if rx.Srv == nil {
        return ErrNilSrv
    }
    go rx.Srv.ListenAndServe()
    time.Sleep(SERVER_DELAY)
    return nil
}

func (rx *HTTPCommRx) StopSrv() error {
    if rx.Srv == nil {
        return ErrNilSrv
    }
    if err := rx.Srv.Close(); err != nil {
        return err
    }
    rx.Srv = rx.ProvisionSrv()
    return nil
}

func (rx *HTTPCommRx) GetAddy() string {
    sPort := strconv.Itoa(rx.Port)
    return (rx.Ip + ":" + sPort)
}

func (rx *HTTPCommRx) ProvisionSrv() *http.Server {
    addy := rx.GetAddy()
    mux := http.NewServeMux()
    mux.HandleFunc("/", getRoot)
    return &http.Server{
            Addr: addy,
            Handler: mux,
            ReadTimeout: CONN_TIMEOUT,
            WriteTimeout: CONN_TIMEOUT,     
    } 
}

func getRoot(w http.ResponseWriter, r *http.Request) {
    var msg []byte
    if r.Body != http.NoBody {
        msg, _ = io.ReadAll(r.Body)
    } else {
        msg = []byte("No body in request.")
    }
    h, _ := json.MarshalIndent(r.Header, "", "  ") 
    reply := fmt.Sprintf("%s\n%s", msg, h)
    w.Write([]byte(reply))
}
