
project(dangel_client_server_lib)

set(SOURCES_SERVER src/Server/Server.cpp;src/Server/User.h;src/Server/Room.h;src/Server/RoomManager.h;src/Server/Server.h)
set(SOURCES_CLIENT src/Client/Client.cpp;src/Client/Client.h)
set(EXE_SERVER ../bin/server)
set(EXE_CLIENT ../bin/client)
set(SRC_PATH ../src)
set(CMAKE_CXX_COMPILER_ID g++)
set(CMAKE_CXX_FLAGS "-fpermissive")

add_executable(${EXE_SERVER} ${SOURCES_SERVER})
target_include_directories(${EXE_SERVER} PRIVATE
     $<BUILD_INTERFACE:${SRC_PATH}>
)

add_executable(${EXE_CLIENT} ${SOURCES_CLIENT})
target_include_directories(${EXE_CLIENT} PRIVATE
     $<BUILD_INTERFACE:${SRC_PATH}>
)
