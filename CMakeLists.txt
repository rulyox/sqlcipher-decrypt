cmake_minimum_required(VERSION 3.15)
project(sqlcipher-decrypt C)

set(CMAKE_C_STANDARD 99)

include_directories(/usr/local/include/sqlcipher)
link_directories(/usr/local/lib/libsqlcipher.a)
link_libraries(sqlcipher)

add_executable(sqlcipher-decrypt main.c)
