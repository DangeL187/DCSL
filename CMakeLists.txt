cmake_minimum_required(VERSION 3.26)
project(DCSL)

# windows - CMakeLists is for mingw13 and Boost 1.84.0 only
# linux - sudo apt install libboost-all-dev

# "boost" folder must be in your project folder
# if you don't want it, please change paths in cmake file
# pay attention: if you use Windows names in BOOST_LIBRARIES are unique for each version of your boost library

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/boost)
    include_directories(${BOOST_ROOT})
    set(BOOST_LIBRARIES boost_system-mgw13-mt-d-x64-1_84 boost_serialization-mgw13-mt-d-x64-1_84)
    set(CMAKE_CXX_FLAGS "-L C:/Users/danii/CLionProjects/DChat/boost/stage/lib/ -std=c++20 -static-libstdc++ -static-libgcc -lboost_system-mgw13-mt-d-x64-1_84 -lboost_serialization-mgw13-mt-d-x64-1_84 -lws2_32 -fpermissive")
endif()
if (UNIX)
    set(BOOST_LIBRARIES boost_system boost_serialization)
    set(CMAKE_CXX_FLAGS "-std=c++20 -static-libstdc++ -static-libgcc -lboost_system -lboost_serialization -fpermissive")
endif()

file(GLOB HEADER_FILES "src/*.h src/**/*.h" "boost/**/*.h")

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(server ${SOURCE_DIR}/Server/Server.cpp ${HEADER_FILES})
add_executable(client ${SOURCE_DIR}/Client/Client.cpp ${HEADER_FILES})

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
