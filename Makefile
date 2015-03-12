build: force_true
	cd src/libhttpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) build
	cd src/httpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) build

all: force_true docs
	cd src/libhttpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) all
	cd src/httpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) all

clean: force_true
	cd src/libhttpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) clean
	cd src/httpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) clean
	rm -rf docs

test: force_true
	cd src/libhttpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) test
	cd src/httpserver && ./test.sh

docs: force_true
	doxygen Doxyfile

force_true:
	true
