build: force_true
	cd src/libhttpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) build
	cd src/httpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) build

all: force_true
	cd src/libhttpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) all
	cd src/httpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) all

clean: force_true
	cd src/libhttpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) clean
	cd src/httpserver && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) clean

force_true:
	true
