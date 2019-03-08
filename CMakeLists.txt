cmake_minimum_required(VERSION 3.9.2)
project(lets_finish C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(lest_finish src/letsfinish.c src/board/board.c src/chance/chance.c src/command/command.c src/game/game.c src/mesinkata/mesinkata.c src/mesinkata/mesinkarakter.c src/player/player.c)