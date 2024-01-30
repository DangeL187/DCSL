------------------------------------------------------------------------
DangeL's Client-Server Lib (DCSL)
------------------------------------------------------------------------
DCSL is a handy library for Linux that will help you setting up
server and client applications way faster than before.
All the basic functionality is already inside this library.
Anyway, feel free to change its code to suit your needs.

Additional information can be found in "doc" directory.
------------------------------------------------------------------------

Usage:
Include Server.h in your main server application.
Include Client.h in your main client application.
Use Server.cpp and Client.cpp as an example.

Prepare to build (Windows):
CMakeLists file is for mingw13 and Boost 1.84.0 only.
The "boost" folder must be in your project folder.
If you don't want it, please change the paths in the cmake file.
Note that if you are using Windows, the names in BOOST_LIBRARIES are
unique for each version of your boost library!

Prepare to build (Linux):
sudo apt install libboost-all-dev

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
