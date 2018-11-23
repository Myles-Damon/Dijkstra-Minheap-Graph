EXEC = proj1
CC = g++
CFLAGS = -c -Wall -std=c++11

# $(EXEC) has the value of shell variable EXEC, which is run.
# run depends on the files main.o util.o heap.o
# $(EXEC) :main.o util.o heap.o
# run is created by the command g++ -o run main.o util.o
# note that the TAB before $(CC) is REQUIRED...
# $(CC) -o $(EXEC) main.o util.o heap.o
# main.o depends on the files main.h main.cpp

proj2: main.o util.o heap.o graph.o
	$(CC) -o proj2 main.o util.o heap.o graph.o
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
# main.o is created by the command g++ -c -Wall main.cpp
#6 # I made this "6" into "#6"
# note that the TAB before $(CC) is REQUIRED...
#$(CC) $(CFLAGS) main.cpp
graph.o :graph.h graph.cpp
	$(CC) $(CFLAGS) graph.cpp
util.o :util.h util.cpp
	$(CC) $(CFLAGS) util.cpp
heap.o :heap.h heap.cpp
	$(CC) $(CFLAGS) heap.cpp
clean :
	rm -f *.o