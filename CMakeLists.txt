cmake_minimum_required(VERSION 3.0)

project(Frontend)

find_package(FLEX  2.6 REQUIRED)
find_package(BISON 2.6 REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(
    HEADERS
    nodes.hpp
    )

BISON_TARGET(
    MyParser
    parser.yy
    ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hh
)

FLEX_TARGET(
    MyScanner
    scanner.ll
    ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

add_executable(
    frontend
    main.cpp
    print.cpp
    driver.cpp
    nodes.cpp
    interpreter.cpp
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyScanner_OUTPUTS}
)

target_include_directories(
    frontend PRIVATE ${Frontend_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
)
