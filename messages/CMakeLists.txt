cmake_minimum_required(VERSION 3.11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug)
project(proto)
include(FindProtobuf)
find_package(Protobuf REQUIRED)
PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HEADER position.proto)
add_library(proto ${PROTO_HEADER} ${PROTO_SRC})
target_link_libraries(proto INTERFACE ${Protobuf_LIBRARIES})