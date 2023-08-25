#!/bin/bash

file=''
exists=1

main() {
    file=$(which $1)
    exists=$?
    echo ""
    if [[ ${exists} -eq 0 ]]; then
        echo "[$1 File Information]"
        echo ""
        echo "[+] which $1: ${file}"
        echo ""
        echo "[+] file ${file}"
        echo "    [*] $(file ${file} | sed 's/, /\n    [*] /g')"
        echo ""
        echo "[+] sha1:     $(shasum ${file})"
        echo "[+] sha256:   $(shasum -a 256 ${file})"
        echo "[+] md5:      $(md5sum ${file})"
        echo ""
    else
        echo "[-] Cannot locate file."
        echo ""
        exit 1
    fi
    echo ""
    exit 0
}

main "$@"
