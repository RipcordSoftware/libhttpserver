GTEST_VER=1.7.0

build: force_true .googletest
	cd src/libhttpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) build
	cd src/httpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) build

all: force_true docs .googletest
	cd src/libhttpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) all
	cd src/httpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) all

clean: force_true
	cd src/libhttpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) clean
	cd src/httpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) clean
	rm -rf docs

.NOTPARALLEL: test
test: force_true .googletest
	cd src/libhttpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) test
	cd src/httpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) build && ./test.sh

docs: force_true
	doxygen Doxyfile
	
.googletest: force_true
	if [ "${CI}" = "true" ]; then \
		curl ftp://ftp.ripcordsoftware.com/pub/gtest-${GTEST_VER}-travis-ci-externals-installed.tar.xz -O && \
		tar xfJ gtest-*; \
	elif [ ! -d externals/gtest-${GTEST_VER}/lib/.libs ]; then \
		mkdir -p externals && \
		cd externals && \
		if [ ! -f gtest-${GTEST_VER}.zip ]; then curl https://googletest.googlecode.com/files/gtest-${GTEST_VER}.zip -O; fi && \
		unzip gtest-${GTEST_VER}.zip && \
		cd gtest-${GTEST_VER} && \
		./configure && \
		make -j 2 && \
		if [ ! -d "../installed/include" ]; then mkdir -p ../installed/include; fi && \
		if [ ! -d "../installed/lib" ]; then mkdir -p ../installed/lib; fi && \
		cp -Rf include/* ../installed/include && \
		cp -Rf lib/.libs/* ../installed/lib; \
	fi

force_true:
	true
