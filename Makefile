INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS)


OBJS 		 := customErrorClass.o binarySearchTree.o main.o 
DEPS 		 := ${INCLUDE_DIRS}/customErrorClass.h Johnson_assign2.h

.PHONY: clean all

all: bst customErrorClass.o binarySearchTree.o main.o


clean:
	rm $(OBJS) bst

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

binarySearchTree.o: Johnson_assign2.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

main.o: main.cpp
	$(CC) -c -o $@ $(CFLAGS) $<

bst: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)