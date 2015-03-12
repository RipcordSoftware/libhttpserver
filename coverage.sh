#!/bin/bash
lcov -b src/libhttpserver --directory src/libhttpserver/build/Debug/GNU-Linux-x86/ --capture --output-file coverage.info
lcov --remove coverage.info 'tests/*' '/usr/*' '*/externals/*' --output-file coverage.info
lcov --list coverage.info
coveralls-lcov coverage.info
