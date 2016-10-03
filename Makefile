GTEST_VER=1.7.0

.PHONY: build all clean test docs .googletest
.NOTPARALLEL: test

build all: .googletest
	cd src/libhttpserver && $(MAKE) $@
	cd src/httpserver && $(MAKE) $@

clean:
	cd src/libhttpserver && $(MAKE) $@
	cd src/httpserver && $(MAKE) $@
	-rm -rf docs

test: .googletest
	cd src/libhttpserver && $(MAKE) $@
	cd src/httpserver && $(MAKE) build && ./test.sh

docs:
	doxygen Doxyfile

.googletest:
	if [ "${CI}" = "true" && "${TRAVIS_OS_NAME}" == "linux" ]; then \
		curl ftp://ftp.ripcordsoftware.com/pub/gtest-${GTEST_VER}-travis-ci-externals-installed.tar.xz -O && \
		tar xfJ gtest-*; \
	elif [ ! -d externals/gtest-${GTEST_VER}/lib/.libs ]; then \
		mkdir -p externals && \
		cd externals && \
		if [ ! -f gtest-${GTEST_VER}.zip ]; then curl ftp://ftp.ripcordsoftware.com/pub/gtest-${GTEST_VER}.zip -O; fi && \
		unzip gtest-${GTEST_VER}.zip && \
		cd gtest-${GTEST_VER} && \
		./configure && \
		$(MAKE) && \
		if [ ! -d "../installed/include" ]; then mkdir -p ../installed/include; fi && \
		if [ ! -d "../installed/lib" ]; then mkdir -p ../installed/lib; fi && \
		cp -Rf include/* ../installed/include && \
		cp -Rf lib/.libs/* ../installed/lib; \
	fi
