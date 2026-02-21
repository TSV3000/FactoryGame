cmake_minimum_required(VERSION 4.0)
project(FactoryGame C)

set(CMAKE_C_STANDARD 11)

set(SOURCES
        src/building/building.h
        src/building/conveyor_belt/conveyor_belt.h
        src/data_structures/vector_array/vector_array.c
        src/data_structures/vector_array/vector_array.h
        src/map/map.c
        src/map/map.h
        src/other/geometry/position.h
        src/other/geometry/direction.h)

add_executable(FactoryGame src/main.c ${SOURCES})

set(TEST_FILES
        test/data_structures/test_vector_array.c
)

add_executable(FactoryGameTest
        ${TEST_FILES}
        ${SOURCES}
)

target_include_directories(FactoryGameTest
        PRIVATE /usr/local/include
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(FactoryGameTest
        PRIVATE criterion
)

enable_testing()
add_test(NAME test_programm
        COMMAND FactoryGameTest
)