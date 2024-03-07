cmake_minimum_required(VERSION 3.0)

project(asio_client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ASIO_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/asio-1.28.0/include)
add_executable(asio_client main.cpp)
target_compile_options(asio_client PUBLIC -DASIO_STANDALONE)

target_include_directories(asio_client PUBLIC ${ASIO_INCLUDE})
target_link_directories(asio_client PUBLIC -lwsock32 -lws2_32)

