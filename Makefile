CC = g++
CFLAGS = -m64

CFILES = server.cpp client.cpp
APPLICATIONS = server client
OBJECTS = server.o client.o
DOBJECTS = server-debug.o client-debug.o

SHELL := pwsh.exe
.SHELLFLAGS := -Command

$(OBJECTS): %.o: source/%.cpp
	$(CC) $(CFLAGS) -o bin/$@ -c $^

$(APPLICATIONS): % : %.o
	$(CC) $(CFLAGS) bin/$@.o -o bin/$@.exe -lws2_32

$(DOBJECTS): %-debug.o: source/%.cpp
	$(CC) $(CFLAGS) -g -o debug/$@ -c $^

clean-all: clean clean-debug

clean:
	del bin\server.o 
	del bin\client.o 
	del bin\server.exe
	del bin\client.exe

clean-debug:
	del debug\server-debug.o
	del debug\client-debug.o
	del debug\server-debug.exe
	del debug\client-debug.exe