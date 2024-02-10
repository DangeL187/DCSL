# DangeL's Client-Server Lib (DCSL)
DCSL is a handy library for Linux that will help you setting up server and client applications way faster than before.
All the basic functionality is already included in this library.
Anyway, feel free to change its code to suit your needs.
## Check out the [documentation](https://github.com/DangeL187/DCSL/blob/main/doc/DCSL.md) for additional information
## Usage:
Include <b>Server.h</b> in your main server application.
Include <b>Client.h</b> in your main client application.
Use [Server.cpp](https://github.com/DangeL187/DCSL/blob/main/src/Server/Server.cpp) and [Client.cpp](https://github.com/DangeL187/DCSL/blob/main/src/Client/Client.cpp) as an example.
## Prepare to build (Windows):
CMakeLists file is for <b>mingw13</b> and <b>Boost 1.84.0</b> only.
The <b>"boost"</b> folder must be in your project folder.
If you dont want it, please change the paths in the cmake file.
Note that if you are using Windows, the names in BOOST_LIBRARIES are
unique for each version of your boost library!
## Prepare to build (Linux):
sudo apt install libboost-all-dev
### How to build:
mkdir build
cd build
cmake ..
make
#### How to run server:
cd bin
./server
#### How to run client:
cd bin
./client
