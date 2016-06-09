cmake_minimum_required(VERSION 3.5)
project(n4s_api)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(LIB lib/srcs/command/__construct.c
        lib/includes/command.h
        lib/srcs/command/__destruct.c
        lib/srcs/command/load.c
        lib/srcs/command/value.c
        lib/srcs/command/send.c
        lib/srcs/command/prepare.c
        lib/srcs/command/listen.c lib/srcs/class/listener/__construct.c lib/includes/class/listener.h lib/srcs/class/listener/__destruct.c lib/srcs/class/listener/listen.c lib/includes/class/car.h lib/srcs/class/car/__construct.c lib/srcs/class/car/__destruct.c lib/srcs/class/car/listen.c lib/srcs/command/config.c lib/srcs/command/execute.c lib/includes/types.h lib/includes/class/remote.h lib/includes/config.h lib/srcs/class/remote/__construct.c lib/srcs/class/remote/__destruct.c lib/srcs/class/remote/connect.c)
set(CLIENT_BIN bin/client/main.c)
set(SERVER_BIN bin/serevr/main.c)

add_library(n4s_api SHARED ${LIB})
target_include_directories(n4s_api PRIVATE lib/includes)

add_executable(n4s_client ${CLIENT_BIN})
target_link_libraries(n4s_client n4s_api)
target_include_directories(n4s_client PRIVATE lib/includes)

add_executable(n4s_server ${SERVER_BIN})
target_link_libraries(n4s_server n4s_api)
target_include_directories(n4s_server PRIVATE lib/includes)