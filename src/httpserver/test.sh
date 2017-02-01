#!/usr/bin/env bash

if [ "$CONF" = "" ]; then
    CONF=Debug
fi

URL=http://localhost:10024
SERVER_ROOT="${PWD}/dist/${CONF}/GNU-Linux-x86"
WEB_ROOT="${SERVER_ROOT}/www"
uris=(`find "${WEB_ROOT}" -type f | cut -c "${#WEB_ROOT}"- | cut -c 3-`)

pushd() { builtin pushd "$1" > /dev/null; }
popd() { builtin popd > /dev/null; }

"${SERVER_ROOT}/httpserver" &

sleep 2

trap 'kill %1' 0

rm -rf tmp.test
mkdir tmp.test
pushd tmp.test

# spider the web files with wget
echo "*******************************************************************"
echo "* spider test"
echo "*******************************************************************"
mkdir spider.test
pushd spider.test
wget -4 -r --no-host-directories ${URL}
if [ $? -ne 0 ]; then exit 1; fi
popd

echo "*******************************************************************"
echo "* HTTP/1.0 test"
echo "*******************************************************************"
mkdir http10.test
pushd http10.test
for uri in "${uris[@]}"
do
    echo "* requesting: ${URL}/${uri}"
    curl -4 -0 ${URL}/${uri} -o ${uri} --create-dirs
    if [ $? -ne 0 ]; then exit 2; fi
    diff --brief ${WEB_ROOT}/${uri} ${uri} > /dev/null
    if [ $? -ne 0 ]; then exit 2; fi
done
popd

echo "*******************************************************************"
echo "* HTTP/1.0 redirect test"
echo "*******************************************************************"
mkdir http10.redirect.test
pushd http10.redirect.test
curl -4 -0 -L ${URL}/ -o index.html
if [ $? -ne 0 ]; then exit 3; fi
if [ ! -f "index.html" ]; then exit 1; fi
diff --brief ${WEB_ROOT}/index.html index.html > /dev/null
if [ $? -ne 0 ]; then exit 3; fi
popd

echo "*******************************************************************"
echo "* HTTP/1.1 redirect test"
echo "*******************************************************************"
mkdir http11.redirect.test
pushd http11.redirect.test
curl -4 -L ${URL} -o index.html
if [ $? -ne 0 ]; then exit 4; fi
if [ ! -f "index.html" ]; then exit 1; fi
diff --brief ${WEB_ROOT}/index.html index.html > /dev/null
if [ $? -ne 0 ]; then exit 4; fi
popd

echo "*******************************************************************"
echo "* HTTP/1.1 close test"
echo "*******************************************************************"
mkdir http11.close.test
pushd http11.close.test
for uri in "${uris[@]}"
do
    echo "* requesting: ${URL}/${uri}"
    curl -4 --header "Connection: close" ${URL}/${uri} -o ${uri} --create-dirs
    if [ $? -ne 0 ]; then exit 5; fi
    diff --brief ${WEB_ROOT}/${uri} ${uri} > /dev/null
    if [ $? -ne 0 ]; then exit 5; fi
done
popd

# request gzipped web files with curl
echo "*******************************************************************"
echo "* gzip test"
echo "*******************************************************************"
mkdir gzip.test
pushd gzip.test
for uri in "${uris[@]}"
do
    if [[ ! ${uri} =~ \.jpg$|\.eot$|\.woff[0-9]?$ ]]; then
        echo "* requesting: ${URL}/${uri}"
        curl -4 --header "Accept-Encoding: gzip" ${URL}/${uri} -o ${uri}.gz --create-dirs
        if [ $? -ne 0 ]; then exit 6; fi

        # if the file is gzipped then test it
        file ${uri}.gz | grep gzip
        if [ $? -eq 0 ]; then
            gunzip -t $uri.gz || exit 6
        else
            exit 6
        fi
    fi
done
popd

# echo to/from the web server (fixed length)
echo "*******************************************************************"
echo "* fixed echo test"
echo "*******************************************************************"
mkdir echo.fixed.test
pushd echo.fixed.test
for uri in "${uris[@]}"
do
    echo "* requesting: ${WEB_ROOT}/${uri}"
    curl -4 -X POST ${URL}/echo --data-binary @${WEB_ROOT}/${uri} -o ${uri} --create-dirs
    if [ $? -ne 0 ]; then exit 7; fi

    diff --brief ${WEB_ROOT}/${uri} ${uri} > /dev/null
    if [ $? -ne 0 ]; then exit 7; fi
done
popd

# echo to/from the web server (chunked)
echo "*******************************************************************"
echo "* chunked echo test"
echo "*******************************************************************"
mkdir echo.chunked.test
pushd echo.chunked.test
for uri in "${uris[@]}"
do
    echo "* requesting: ${WEB_ROOT}/${uri}"
    curl -4 -X POST ${URL}/echo --header "Transfer-Encoding: chunked" --data-binary @${WEB_ROOT}/${uri} -o ${uri} --create-dirs
    if [ $? -ne 0 ]; then exit 8; fi

    diff --brief ${WEB_ROOT}/${uri} ${uri} > /dev/null
    if [ $? -ne 0 ]; then exit 8; fi
done
popd

popd

rm -rf tmp.test
