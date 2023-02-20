cmake_minimum_required(VERSION 3.11)

project(posgen VERSION 1.0)

# Two different implementations of position generator program based on how many zmq sockets are used.
# Hence, uncomment only one of the below two lines
set(SRC_FILES src/position_data.cpp src/rand_pos_gen.cpp)
#set(SRC_FILES src/position_data.cpp src/rand_pos_gen_one_skt.cpp)
add_executable(posgen ${SRC_FILES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/header)

find_package(cppzmq)
add_subdirectory(messages)
set(PROTOBUF_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/messages)
include_directories(${PROTOBUF_INCLUDE_DIR})

target_link_libraries(posgen PUBLIC cppzmq pthread proto)
 
