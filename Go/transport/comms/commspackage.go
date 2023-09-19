package comms

import (
    "errors"
    "net/http"
    "time"
)

var (
    CONN_TIMEOUT time.Duration = 10 * time.Second
    SERVER_DELAY = 2 * time.Second
    USER_AGENT string = "Mozilla/5.0 (Android 4.4; Mobile; rv:41.0) Geko/41.0 Firefox/41.0"
    ErrNilSrv error = errors.New("server is nil")
    ErrComDNE error = errors.New("Comms package does not exist")
)

type CommsPackage interface {
    SendJSON(msg interface{}, dst string) (*http.Response, error)
    Get(dst string) (*http.Response, error)
}

func NewCommsPackage(c string) (CommsPackage, error) {
    switch c {
    case "http":
        tx := NewHTTPCommTX()
        return &tx, nil
    default:
        return nil, ErrComDNE
    }
}
