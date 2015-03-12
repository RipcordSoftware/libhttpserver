#!/bin/bash

SERVER_ROOT=${PWD}/dist/Debug/GNU-Linux-x86
WEB_ROOT=${SERVER_ROOT}/www

${SERVER_ROOT}/httpserver &

trap 'kill %1' 0

mkdir -p tmp.test
cd tmp.test

# spider the web files with wget
mkdir spider.test
cd spider.test
wget -4 -r --no-host-directories http://localhost:10024/ 
cd ..

# request the web files with curl
mkdir gzip.test
cd gzip.test
uris=(`find $WEB_ROOT -type f -printf "%P\n"`)
for uri in "${uris[@]}"
do
    curl -4 --header "Accept-Encoding: gzip" http://localhost:10024/${uri} -o ${uri}.gz --create-dirs
    if [ "$?" -ne 0 ]; then exit $?; fi

    # if the file is gzipped then test it
    file ${uri}.gz | grep gzip
    if [ "$?" -eq 0 ]; then
        gunzip -t $uri.gz || exit $?
    fi
done
cd ..

cd ..
rm -rf tmp.test
