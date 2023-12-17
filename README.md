# Windows Local Server

Simple local server made to run on Windows machines. The server's task is been able to create a chat room between two computers on same local connection.

## Why does it run only on Windows?

That's because I'm using the `<winsock2.h>` library. As the name suggests, it's made to create server sockets for Windows machines.

On my recently research I found there is some similar library to Linux too. But as my OS is Windows, I see no purpose on not using the Windows library.

## Some warnings

This code is not 100% of my authorship, it's made based on this repository [cpp-networking][], I just made some modifications to fulfill my needings.

## Current status

The code is working as is meant do be. You can send messages between two terminals windows. I haven't tested it yet on two different machines; probably it would require some changes at the IP configurations.

## Multi-threading

You can check out in the [source/includes.hpp], the `<threads>` library is included. But why?

The program must be constantly checking if new data was received from the server. I made this check code be a separated thread.

This multi-thread code can be seen on [source/client.cpp], in fact, there isn't much code on [source/server.cpp]. I know this may not be a safe approach, write many lines on client side, but this is my first server code, so be less harsh ok?

## How to build the program?

There is a Makefile ready to it if you use the GNU Compiler. If not, you still can check the compile flags used on it to compile on CMake, clang or other compile I don't know.

Using the Makefile you can simply write:

```sh
Make client
Make server
```

You must be at the parent folder of the repository.

## How to run the program?

After compiling it, you can find the binaries at the [bin][] folder(if you compiled it using the Makefile). Change your working directory to there and run:

```sh
.\server
```

It will open a server terminal window. To log in clients, you must open, at least two, other terminal windows and run:

```sh
.\client
```

on each of the windows. After that you can start sending and receiving messages through LAN connection.

[cpp-networking]: https://github.com/codehoose/cpp-networking/tree/main
[source/includes.hpp]: source/includes.hpp
[source/client.cpp]: source/client.cpp
[source/server.cpp]: source/server.cpp
[bin]: bin