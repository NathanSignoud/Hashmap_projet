LIB=$(wildcard lib/*.h)

all : exx

bin/stack.o : src/stack.c $(LIB)
	gcc -c $< -o $@

bin/tree.o : src/tree.c $(LIB)
	gcc -c $< -o $@

bin/hashmap.o : src/hashmap.c $(LIB)
	gcc -c $< -o $@

bin/main.o : src/main.c $(LIB)
	gcc -c $< -o $@

exx : bin/stack.o bin/tree.o bin/hashmap.o bin/main.o
	ar -rcs libhashmap.a bin/stack.o bin/tree.o bin/hashmap.o
	gcc -fsanitize=address bin/main.o libhashmap.a -o $@
	doxygen

clean:
	rm -f bin/*.o
	rm -f exx
	rm -f *.a

