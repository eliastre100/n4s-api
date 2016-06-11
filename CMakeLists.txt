cmake_minimum_required(VERSION 3.5)
project(n4s_api)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(LIB lib/srcs/class/listener/__construct.c
        lib/includes/class/listener.h
        lib/srcs/class/listener/__destruct.c
        lib/srcs/class/listener/connect.c
        lib/includes/class/car.h
        lib/srcs/class/car/__construct.c
        lib/srcs/class/car/__destruct.c
        lib/includes/types.h
        lib/includes/class/remote.h
        lib/includes/config.h
        lib/srcs/class/remote/__construct.c
        lib/srcs/class/remote/__destruct.c
        lib/srcs/class/remote/connect.c
        lib/includes/class/command.h
        lib/srcs/class/command/__construct.c
        lib/srcs/class/command/__destruct.c
        lib/srcs/class/command/load.c
        lib/srcs/class/command/set_value.c
        lib/srcs/class/command/send.c
        lib/srcs/class/command/import.c
        lib/srcs/class/command/apply.c
        lib/srcs/class/listener/listen.c lib/srcs/utils/close_io.c lib/includes/utils.h lib/srcs/class/car/listen.c lib/srcs/class/listener/disconnect.c lib/includes/class/converter.h lib/srcs/class/converter/__construct.c lib/srcs/class/converter/__destruct.c lib/srcs/class/converter/export.c lib/srcs/class/converter/open.c lib/srcs/class/converter/close.c lib/srcs/class/converter/import.c lib/srcs/class/converter/calculations.c)
set(CLIENT_BIN bin/client/main.c)
set(SERVER_BIN bin/serevr/main.c)
set(CONVERTER_BIN bin/converter/main.c)

add_library(n4s_api SHARED ${LIB})
target_include_directories(n4s_api PRIVATE lib/includes)
target_link_libraries(n4s_api pthread)

add_executable(n4s_client ${CLIENT_BIN})
target_link_libraries(n4s_client n4s_api)
target_include_directories(n4s_client PRIVATE lib/includes)

add_executable(n4s_server ${SERVER_BIN})
target_link_libraries(n4s_server n4s_api)
target_include_directories(n4s_server PRIVATE lib/includes)

add_executable(n4s_converter ${CONVERTER_BIN})
target_link_libraries(n4s_converter n4s_api)
target_include_directories(n4s_converter PRIVATE lib/includes)