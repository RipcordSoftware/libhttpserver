all: force_true
	cd src/libhttpserver; $(MAKE) $(MFLAGS)

clean: force_true
	cd src/libhttpserver; $(MAKE) clean

force_true:
	true
