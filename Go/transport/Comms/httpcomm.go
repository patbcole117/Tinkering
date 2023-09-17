package comms

import (
	"net/http"
)

type HttpComm struct {
	C *http.Client
}

func NewHTTPComm() {

}