cmake_minimum_required(VERSION 3.10)
project(ImageLoader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)


set(COMMON_SRCS
    src/message.cpp
    src/socket.cpp
    src/client_socket.cpp
    src/serveur_socket.cpp
)

add_executable(open_image src/open_image.cpp src/image.cpp)
add_executable(client src/main_client.cpp src/client.cpp ${COMMON_SRCS})
add_executable(server src/main_serveur.cpp src/serveur.cpp ${COMMON_SRCS})

target_link_libraries(open_image sfml-graphics sfml-window sfml-system)