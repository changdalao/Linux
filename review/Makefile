.PHONY: all clean

all : write main

main : main.o libadd.so
	gcc $< -o $@ -L. -ladd
	
write : write.o
	gcc $^ -o $@
	
libadd.so : add.o
	gcc -fPIC -shared -o $@ $^
	
%.o : %.c
	gcc -c $^ -o $@
	
clean:
	rm -rf *.o 
