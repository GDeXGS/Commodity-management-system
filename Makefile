

#export IMAGE=ep
#export LIB=libep.so
export IMAGE=main
export LIB=libmain.a

all:
	$(MAKE) -C arch
	$(MAKE) -C src
	
clean:
	$(MAKE) $@ -C src
	$(MAKE) $@ -C arch
.PHONY:clean