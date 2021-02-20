
SRC=$(wildcard *c)
OBJ=$(SRC:%.c=%.o)
#LIB?=libtest.so
LIB?=libtest.a

all:$(OBJ) $(LIB) mv

$(OBJ):%.o:%.c
	$(CC) $(^) -o $(@) -c -I ../include/
	#$(CC) $(^) -o $(@) -c -fPIC -I ../include/
	
$(LIB):$(OBJ)	
	ar -crv $(@) $(^)
	#$(CC) $(^) -shared -o $(@)
	
mv:
	sudo mv $(LIB) ../lib/

clean:
	$(RM) $(OBJ) ../lib/$(LIB) -rf
.PHONY:clean
	
	