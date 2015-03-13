#!/bin/bash
lcov -b src/libhttpserver --directory src/libhttpserver/build/Debug/GNU-Linux-x86/ --capture --output-file coverage.info
lcov --remove coverage.info 'tests/*' '/usr/*' '*/externals/*' --output-file coverage.info
lcov --list coverage.info
if [ "$CI" = "true" ] && [ "$TRAVIS" = "true" ]; then
    coveralls-lcov coverage.info
else
    rm -rf coverage
    mkdir -p coverage
    cd coverage
    genhtml ../coverage.info
    cd ..
fi
