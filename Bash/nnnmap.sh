#!/bin/bash

name_opt=''
out_opt=''
rate_opt=1000
udp_opt=false
srv_opt=false
ports=''

main () {

        while getopts 'n:o:r:UT' opt; do
                case "${opt}" in

                        n) name_opt=${OPTARG} ;;
                        o) out_opt=${OPTARG} ;;
                        r) rate_opt=${OPTARG} ;;
                        U) udp_opt=true ;;
                        T) srv_opt=true ;;
                        *) usage ;;

                esac
        done

        if [[ ${name_opt} != '' && ${out_opt} != '' ]]; then

                check_host
                check_output
                if ${srv_opt}; then
                        scan_srv
                fi
                if ${udp_opt}; then
                        scan_udp
                fi
        else
                usage
        fi

}

check_host(){
        echo 'Checking /etc/host...'

        cat /etc/hosts | grep -P "(\s|^)${name_opt}(\s|$)"
        if [[ $? -eq 0 ]]; then
               echo 'Found in /etc/hosts!'
        else
                read -p 'The host was not found in /etc/hosts. Would you like to add it (y/n)?' q_add_host
                if [[ ${q_add_host} = 'y' || ${q_add_host} = 'Y' ]]; then
                        read -p 'Please provide the IP: ' ip_address
                        read -p 'Please provide the hostname: ' hostname
                        hostname_entry="${ip_address}   ${hostname}"
                        echo "${hostname_entry}"
                        read -p 'Add to /etc/hosts (y/n)?' q_add_host

                        if [[ ${q_add_host} = 'y' || ${q_add_host} = 'Y' ]]; then
                                echo "${hostname_entry}" >> /etc/hosts
                                echo "${hostname_entry} has been added to /etc/hosts!"
                                echo ''
                                cat /etc/hosts
                                echo ''
                        fi
                fi
        fi

        echo ''
}

check_output(){

        echo 'Verifying output...'

        if [[ ! -d ${out_opt}  ]]; then
                read -p ".${out_opt} does not exist, would you like to create it (y/n)?" q_mkdir
                if [[ ${q_mkdir} = 'y' || ${q_mkdir} = 'Y' ]]; then
                        mkdir -p ${out_opt}
                        echo ".${out_opt} has been created!"
                else
                        echo 'Directory was not created. Exiting...'
                        exit 1
                fi
        fi

        echo ''
}

scan_udp() {

        echo 'Scanning UDP...'

        nmap -sU -p- --min-rate ${rate_opt} -oA ${out_opt}udp_scan ${name_opt}

        echo ''
}

scan_tcp() {

        echo 'Scanning TCP...'

        ports=$(nmap -sT -p- --min-rate ${rate_opt} -oA ${out_opt}tcp_scan ${name_opt} \
        | grep ^[0-9] \
        | cut -d '/' -f 1 \
        | tr '\n' ',' \
        | sed s/,$//)

        echo "Ports: ${ports}"
        echo ''
}

scan_srv() {

        scan_tcp

        echo 'Scanning services...'

        nmap -PN -sC -sV -O -p${ports} --min-rate ${rate_opt} -oA ${out_opt}srv_scan ${name_opt}

        echo ''
}

usage() {

        echo "$0 -n HOST -o OUTPUT-PATH/ -r MIN-RATE" 1>&2
        exit 1

}

main "$@"