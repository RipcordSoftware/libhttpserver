#!/bin/bash

URL=http://localhost:10024
SERVER_ROOT=${PWD}/dist/Debug/GNU-Linux-x86
WEB_ROOT=${SERVER_ROOT}/www
uris=(`find $WEB_ROOT -type f -printf "%P\n"`)

${SERVER_ROOT}/httpserver &

trap 'kill %1' 0

mkdir -p tmp.test
cd tmp.test

# spider the web files with wget
echo "*******************************************************************"
echo "* spider test"
echo "*******************************************************************"
mkdir spider.test
cd spider.test
wget -4 -r --no-host-directories ${URL}
if [ "$?" -ne 0 ]; then exit $?; fi
cd ..

echo "*******************************************************************"
echo "* HTTP/1.0 test"
echo "*******************************************************************"
mkdir http10.test
cd http10.test
for uri in "${uris[@]}"
do
    echo "* requesting: ${URL}/${uri}"
    curl -4 -0 ${URL}/${uri} -o ${uri} --create-dirs
    if [ "$?" -ne 0 ]; then exit $?; fi
    diff --brief ${WEB_ROOT}/${uri} ${uri} > /dev/null
    if [ "$?" -ne 0 ]; then exit $?; fi
done
cd ..

echo "*******************************************************************"
echo "* HTTP/1.0 redirect test"
echo "*******************************************************************"
mkdir http10.redirect.test
cd http10.redirect.test
curl -4 -0 -L ${URL}/ -o index.html
if [ "$?" -ne 0 ]; then exit $?; fi
if [ ! -f "index.html" ]; then exit 1; fi
diff --brief ${WEB_ROOT}/index.html index.html > /dev/null
if [ "$?" -ne 0 ]; then exit $?; fi
cd ..

echo "*******************************************************************"
echo "* HTTP/1.1 redirect test"
echo "*******************************************************************"
mkdir http11.redirect.test
cd http11.redirect.test
curl -4 -L ${URL} -o index.html
if [ "$?" -ne 0 ]; then exit $?; fi
if [ ! -f "index.html" ]; then exit 1; fi
diff --brief ${WEB_ROOT}/index.html index.html > /dev/null
if [ "$?" -ne 0 ]; then exit $?; fi
cd ..

echo "*******************************************************************"
echo "* HTTP/1.1 close test"
echo "*******************************************************************"
mkdir http11.close.test
cd http11.close.test
for uri in "${uris[@]}"
do
    echo "* requesting: ${URL}/${uri}"
    curl -4 --header "Connection: close" ${URL}/${uri} -o ${uri} --create-dirs
    if [ "$?" -ne 0 ]; then exit $?; fi
    diff --brief ${WEB_ROOT}/${uri} ${uri} > /dev/null
    if [ "$?" -ne 0 ]; then exit $?; fi
done
cd ..

# request gzipped web files with curl
echo "*******************************************************************"
echo "* gzip test"
echo "*******************************************************************"
mkdir gzip.test
cd gzip.test
for uri in "${uris[@]}"
do
    echo "* requesting: ${URL}/${uri}"
    curl -4 --header "Accept-Encoding: gzip" ${URL}/${uri} -o ${uri}.gz --create-dirs
    if [ "$?" -ne 0 ]; then exit $?; fi

    # if the file is gzipped then test it
    file ${uri}.gz | grep gzip
    if [ "$?" -eq 0 ]; then
        gunzip -t $uri.gz || exit $?
    fi
done
cd ..

# echo to/from the web server (fixed length)
echo "*******************************************************************"
echo "* fixed echo test"
echo "*******************************************************************"
mkdir echo.fixed.test
cd echo.fixed.test
for uri in "${uris[@]}"
do
    echo "* requesting: ${WEB_ROOT}/${uri}"
    curl -4 -X POST ${URL}/echo --data-binary @${WEB_ROOT}/${uri} -o ${uri} --create-dirs
    if [ "$?" -ne 0 ]; then exit $?; fi

    diff --brief ${WEB_ROOT}/${uri} ${uri} > /dev/null
    if [ "$?" -ne 0 ]; then exit $?; fi
done
cd ..

# echo to/from the web server (chunked)
echo "*******************************************************************"
echo "* chunked echo test"
echo "*******************************************************************"
mkdir echo.chunked.test
cd echo.chunked.test
for uri in "${uris[@]}"
do
    echo "* requesting: ${WEB_ROOT}/${uri}"
    curl -4 -X POST ${URL}/echo --header "Transfer-Encoding: chunked" --data-binary @${WEB_ROOT}/${uri} -o ${uri} --create-dirs
    if [ "$?" -ne 0 ]; then exit $?; fi

    diff --brief ${WEB_ROOT}/${uri} ${uri} > /dev/null
    if [ "$?" -ne 0 ]; then exit $?; fi
done
cd ..

cd ..
rm -rf tmp.test
