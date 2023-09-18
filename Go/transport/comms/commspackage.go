package comms

type CommsPackage interface {
	SendJson(msg []byte, dst string)
    Get(dst string)
}
