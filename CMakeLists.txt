cmake_minimum_required(VERSION 3.26)
project(DCSL)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    set(BOOST_ROOT "D:/boost")
    include_directories(${BOOST_ROOT})
    link_directories(${BOOST_ROOT}/stage/lib)
    set(BOOST_LIBRARIES boost_system-mgw13-mt-d-x64-1_84 boost_serialization-mgw13-mt-d-x64-1_84)  # these values may differ from yours!
    set(CMAKE_CXX_FLAGS "-lboost_system-mgw13-mt-d-x64-1_84 -lboost_serialization-mgw13-mt-d-x64-1_84 -lws2_32 -fpermissive")
endif()
if (UNIX)
    set(BOOST_LIBRARIES boost_system boost_serialization)
    set(CMAKE_CXX_FLAGS "-lboost_system -lboost_serialization -fpermissive")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB HEADER_FILES  "include/**/*.h"
                        "include/*.h")
file(GLOB SOURCE_FILES  "src/**/*.cpp"
                        "src/*.cpp")

add_library(DCSL STATIC ${SOURCE_FILES} ${HEADER_FILES})

if (WIN32)
    target_link_libraries(DCSL ${BOOST_LIBRARIES} wsock32 ws2_32)
endif()
if (UNIX)
    target_link_libraries(DCSL ${BOOST_LIBRARIES})
endif()
