cmake_minimum_required(VERSION 3.20)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR})

set(RESOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/resource.rc)
set(RESOURCE_COMPILED ${CMAKE_CURRENT_BINARY_DIR}/resource.o)

add_custom_command(
    OUTPUT ${RESOURCE_COMPILED}
    COMMAND windres ${RESOURCE_FILE} -O coff -o ${RESOURCE_COMPILED}
    DEPENDS ${RESOURCE_FILE}
    COMMENT "Compiling Windows resources"
)

set(SOURCES main.cpp ${RESOURCE_COMPILED})
add_executable(${PROJECT_NAME} ${SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE TRUE)

target_link_libraries(${PROJECT_NAME} PRIVATE -Wl,--subsystem,windows)
