CMAKE_MINIMUM_REQUIRED(VERSION 3.20.0)

PROJECT(duo
    VERSION 0.0.0
    LANGUAGES C)

FIND_PACKAGE(FLEX)
FIND_PACKAGE(BISON)

SET(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
SET(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

flex_target(LEXER
    ${SOURCES_DIR}/lexer.l
    ${SOURCES_DIR}/lexer.c
    DEFINES_FILE ${SOURCES_DIR}/lexer.h)

bison_target(PARSER
    ${SOURCES_DIR}/parser.y
    ${SOURCES_DIR}/parser.c
    DEFINES_FILE ${SOURCES_DIR}/parser.h)

add_flex_bison_dependency(LEXER PARSER)

INCLUDE_DIRECTORIES(${HEADERS_DIR})

ADD_LIBRARY(duo01 SHARED
    ${SOURCES_DIR}/base.c
    ${SOURCES_DIR}/type.c
    ${SOURCES_DIR}/none.c
    ${SOURCES_DIR}/function.c
    ${SOURCES_DIR}/int.c
    ${SOURCES_DIR}/float.c
    ${SOURCES_DIR}/bool.c
    ${SOURCES_DIR}/table.c
    ${SOURCES_DIR}/string.c
    ${SOURCES_DIR}/std.c
    ${SOURCES_DIR}/lexer.c
    ${SOURCES_DIR}/parser.c)

ADD_EXECUTABLE(duo
    ${SOURCES_DIR}/main.c)

TARGET_LINK_LIBRARIES(duo01
    dl)

TARGET_LINK_LIBRARIES(duo
    duo01)