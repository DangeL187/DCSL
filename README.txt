------------------------------------------------------------------------
DangeL's Client-Server Lib (DCSL)
------------------------------------------------------------------------
DCSL is a handy library for Linux that will help you setting up server and client
applications way faster than before.
All the basic functionality is already inside this library.
Anyway, feel free to change its code to suit your needs.

Additional information can be found in "doc" directory.
------------------------------------------------------------------------

Usage:
Include Server.h in your main server application.
Include Client.h in your main client application.
Use Server.cpp and Client.cpp as an example.

How to build:
mkdir build
cd build
cmake ..
make

How to run server:
cd bin
./server

How to run client:
cd bin
./client
