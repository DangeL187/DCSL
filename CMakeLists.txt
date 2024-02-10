cmake_minimum_required(VERSION 3.26)
project(DCSL)

# windows - CMakeLists is for mingw13 and Boost 1.84.0 only
# linux - sudo apt install libboost-all-dev

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    set(BOOST_ROOT "C:/boost")  # set the boost location
    include_directories(${BOOST_ROOT})
    link_directories(${BOOST_ROOT}/stage/lib)
    set(BOOST_LIBRARIES boost_system-mgw13-mt-d-x64-1_84 boost_serialization-mgw13-mt-d-x64-1_84)  # these values may differ from yours!
    set(CMAKE_CXX_FLAGS "-std=c++20 -static-libstdc++ -static-libgcc -lboost_system-mgw13-mt-d-x64-1_84 -lboost_serialization-mgw13-mt-d-x64-1_84 -lws2_32 -fpermissive")
endif()
if (UNIX)
    set(BOOST_LIBRARIES boost_system boost_serialization)
    set(CMAKE_CXX_FLAGS "-std=c++20 -static-libstdc++ -static-libgcc -lboost_system -lboost_serialization -fpermissive")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB HEADER_FILES_SERVER "include/*.h" "include/Server/*.h")
file(GLOB HEADER_FILES_CLIENT "include/*.h" "include/Client/*.h")

set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(server ${SOURCE_DIR}/Server.cpp ${HEADER_FILES_SERVER})
add_executable(client ${SOURCE_DIR}/Client.cpp ${HEADER_FILES_CLIENT})

if (WIN32)
    target_link_libraries(server ${BOOST_LIBRARIES} wsock32 ws2_32)
    target_link_libraries(client ${BOOST_LIBRARIES} wsock32 ws2_32)
endif()
if (UNIX)
    target_link_libraries(server ${BOOST_LIBRARIES})
    target_link_libraries(client ${BOOST_LIBRARIES})
endif()

set_target_properties(server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set_target_properties(client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
