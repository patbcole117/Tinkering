package comms

type Comm interface {
	Tx(msg []byte)
}