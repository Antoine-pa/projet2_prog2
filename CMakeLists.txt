cmake_minimum_required(VERSION 3.10)
project(projet2)

set(CMAKE_CXX_STANDARD 17)

set(COMMON_SRCS
    src/message.cpp
    src/socket.cpp
    src/client_socket.cpp
    src/serveur_socket.cpp
    src/image.cpp
)

add_executable(client src/main_client.cpp src/client.cpp ${COMMON_SRCS})
add_executable(server src/main_serveur.cpp src/serveur.cpp ${COMMON_SRCS})
