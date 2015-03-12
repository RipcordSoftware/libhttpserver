#!/bin/bash
dist/Debug/GNU-Linux-x86/httpserver &

mkdir -p test.tmp
cd test.tmp

# spider the web files with wget
wget -4 -r http://localhost:10024/ -R js,css,jpg,png

# request the web files with curl
uris=(`find ../dist/Debug/GNU-Linux-x86/www/ -type f -printf "%P\n"`)
for uri in "${uris[@]}"
do
    curl --header "Accept-Encoding: gzip" http://localhost:10024/${uri} -O
done

kill %1

cd ..
rm -rf test.tmp
