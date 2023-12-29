package main

import (
    "bytes"
    "fmt"
)

const chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

func deBruijn(k, n int) string {
    alphabet := chars[0:k]
    a := make([]byte, k*n)
    var seq []byte
    var db func(int, int) // recursive closure
    db = func(t, p int) {
        if t > n {
            if n%p == 0 {
                seq = append(seq, a[1:p+1]...)
            }
        } else {
            a[t] = a[t-p]
            db(t+1, p)
            for j := int(a[t-p] + 1); j < k; j++ {
                a[t] = byte(j)
                db(t+1, t)
            }
        }
    }
    db(1, 1)
    var buf bytes.Buffer
    for _, i := range seq {
        buf.WriteByte(alphabet[i])
    }
    b := buf.String()
    return b + b[0:n-1]
}

func allDigits(s string) bool {
    for _, b := range s {
        if b < '0' || b > '9' {
            return false
        }
    }
    return true
}


func main() {
    db := deBruijn(4, 5)
    le := len(db)
    fmt.Println("The length of the de Bruijn sequence is", le)
    fmt.Println(db)

    bytes := []byte(db)
	fmt.Println(printBytes(bytes))
}

func printBytes(ar_b []byte) string {
    s := ""
    for i := 0; i < len(ar_b); i++ {
        if i%(16) == 0 {
            s = s + "\n"
        }
        s = s + fmt.Sprintf("\\x%02x", ar_b[i])
    }
    s = s + "\n"
    return s
}