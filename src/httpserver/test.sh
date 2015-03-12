#!/bin/bash
dist/Debug/GNU-Linux-x86/httpserver &
mkdir -p test.tmp
cd test.tmp
wget -4 -r http://localhost:10024/ -R js,css,jpg,png
kill %1
cd ..
rm -rf test.tmp
