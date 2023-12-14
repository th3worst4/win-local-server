# Windows Local Server

Simple local server made to run on Windows machines. The server's task is been able to create a chat room between two computers on same local connection.

## Why does it run only on Windows?

That's because I'm using the `<winsock2.h>` library. As the name sugests, it's made to create server sockets for Windows machines.

On my recently researchs I found there is some similar library to Linux too. But as my OS is Windows, I see no purpose on not using the Windows library.

## Some warnings

This code is not 100% of my authorship, it's made based on this repository [cpp-networking][], I just made some modifications to fulfill my needings.

## Current status

The code is in fact working, but not as I expected. Some undesired behavior can be seen at run-time; I'm working to improve it.

This undesired behavior this a consequence of using multi-threading. You can check out in the [source/includes.hpp], the `<threads>` library is included. But why?

The program must be constantly check if new data was received from the server. I made this check code be a separated thread.

This multi-thread code can be seen on [source/client.cpp], in fact, there isn't much code on [source/server.cpp]. I know this may not be a safe approach, write many lines on client side, but this is my first server code, so be less harch ok?

[cpp-networking]: https://github.com/codehoose/cpp-networking/tree/main
