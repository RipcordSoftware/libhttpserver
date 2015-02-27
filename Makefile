all: force_true
	cd src/libhttpserver; $(MAKE) $(MFLAGS)
	cd src/httpserver; $(MAKE) $(MFLAGS)

clean: force_true
	cd src/libhttpserver; $(MAKE) clean
	cd src/httpserver; $(MAKE) clean

force_true:
	true
