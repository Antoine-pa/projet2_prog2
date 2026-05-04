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
    src/image_editor.cpp
)

add_executable(open_image src/open_image.cpp src/image.cpp)
add_executable(client src/main_client.cpp src/client.cpp ${COMMON_SRCS})
add_executable(server src/main_serveur.cpp src/serveur.cpp src/displayer_manager.cpp ${COMMON_SRCS})
add_executable(displayer src/main_displayer.cpp src/displayer.cpp ${COMMON_SRCS})
add_executable(pxlwar_client_test test/main_client_test.cpp src/client.cpp src/displayer.cpp ${COMMON_SRCS})

target_link_libraries(open_image sfml-graphics sfml-window sfml-system)
target_link_libraries(client sfml-graphics sfml-window sfml-system)
target_link_libraries(server sfml-graphics sfml-window sfml-system pthread)
target_link_libraries(displayer sfml-graphics sfml-window sfml-system pthread)
target_link_libraries(pxlwar_client_test sfml-graphics sfml-window sfml-system)