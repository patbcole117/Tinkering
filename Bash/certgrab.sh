#!/bin/bash

domain_opt=''
out_opt=false
silent_opt=false

main(){

        while getopts 'd:os' opt; do
                case "${opt}" in

                        d) domain_opt=${OPTARG} ;;
                        o) out_opt=true ;;
                        s) silent_opt=true ;;
                esac
        done

        if [[ ${domain_opt} != '' ]]; then
                get_subdomains
        else
                usage
        fi

}

get_subdomains() {

        echo " Grabbing subdomains based on cert information (${domain_opt})..."

        list=$(curl -s "https://crt.sh/?q=${domain_opt}&output=json" | jq -r '.[] | "\(.name_value)\n\(.common_name)"' | sort -u)

        if ${silent_opt}; then
                echo "${list}" > ${domain_opt}_crt.sh.txt
        elif ${out_opt}; then
                echo "${list}" | tee ${domain_opt}_crt.sh.txt
        else
                echo "${list}"
        fi

}

usage() {

        echo "${0} -d <DOMAIN> [-o output, -s silent]" 1>&2
        exit 1
        
}

main "$@"