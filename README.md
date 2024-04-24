# DangeL's Client-Server Lib (DCSL)
DCSL is a handy cross-platform library that will help you setting up server and client applications way faster than before.

All the basic functionality is already included in this library.

Anyway, feel free to change its code to suit your needs.
## Check out the [documentation](https://github.com/DangeL187/DCSL/blob/main/doc/DCSL.md) for additional information

## Example:
[SyncWithMe](https://github.com/DangeL187/SyncWithMe) is written using DCSL

## Prepare to build (Windows):
CMakeLists file is for <b>mingw13</b> and <b>Boost 1.84.0</b> only.

<p>Pay attention to the location of the <b>"boost"</b> folder!</p>
<p>In my case, it is located in "C:\boost".</p>
<p>If you want it to be somewhere else, please change the paths in the cmake file.</p>

Note that if you are using Windows, the names in BOOST_LIBRARIES are
unique for each version of your boost library!
## Prepare to build (Linux):
sudo apt install libboost-all-dev
### How to build:

```
mkdir build
cd build
cmake ..
make
```

#### How to run server:
cd bin
./server
#### How to run client:
cd bin
./client
