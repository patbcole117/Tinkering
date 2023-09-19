package comms

import (
    "errors"
    "net/http"
)

var ErrNilSrv error = errors.New("server is nil")
var ErrComDNE error = errors.New("Comms package does not exist")

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
