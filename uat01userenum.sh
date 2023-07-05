#!/bin/bash

cat ${1} | while read user
do
    echo ${user}
    echo
    curl -s -X POST "http://uat01-eu.intranet.trilocor.local/auth/register" -d "{\"username\":\"${user}\", \"password\":\"password\", \"email\":\"${user}@trilocor.local\"}" -H 'Content-Type: application/json'
done
