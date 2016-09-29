make CC=${_CC} CXX=$(_CXX) -j 2 all && make CC=${_CC} CXX=$(_CXX) -j 2 test

if [[ "${COV}" != "" ]]; then
    ./coverage.sh ${_COV}
fi
