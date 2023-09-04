
project(dangel_client_server_lib)

set(SOURCE_EXE src/Server/Server.cpp)
set(SOURCE_EXE2 src/Client/Client.cpp)
set(CMAKE_CXX_COMPILER_ID g++)
set(CMAKE_CXX_FLAGS "-fpermissive")

add_executable(../bin/server ${SOURCE_EXE})
add_executable(../bin/client ${SOURCE_EXE2})

