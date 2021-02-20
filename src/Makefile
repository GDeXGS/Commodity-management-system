
SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.o)
IMAGE?=test
LIB?=libtest.so


#LIBNAME=$(LIB:lib%.so=% )
LIBNAME=$(LIB:lib%.a=% )
LIBPATH=../lib
COM_FLAG=-L $(LIBPATH) -l$(LIBNAME)


all:$(OBJ) $(IMAGE) mv

$(OBJ):%.o:%.c
	$(CC) $(^) -o $(@) -c -I ../include/
	
$(IMAGE):$(OBJ)
	$(CC) $(^) -o $(@) $(COM_FLAG)

mv:
	mv $(IMAGE) ../
	
clean:
	$(RM) $(OBJ) ../$(IMAGE) -rf
.PHONY:clean




