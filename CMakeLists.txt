CMAKE_MINIMUM_REQUIRED(VERSION 3.20.0)

PROJECT(duo
    VERSION 0.1.0
    LANGUAGES C)

SET(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
SET(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

FIND_PACKAGE(FLEX  REQUIRED)
FIND_PACKAGE(BISON REQUIRED)

INCLUDE_DIRECTORIES(${HEADERS_DIR})

flex_target(LEXER
    ${SOURCES_DIR}/lexer.l
    ${SOURCES_DIR}/lexer.c
    DEFINES_FILE ${SOURCES_DIR}/lexer.h)

bison_target(PARSER
    ${SOURCES_DIR}/parser.y
    ${SOURCES_DIR}/parser.c
    DEFINES_FILE ${SOURCES_DIR}/parser.h)

add_flex_bison_dependency(LEXER PARSER)

ADD_LIBRARY(duo01 SHARED
    ${SOURCES_DIR}/bytearray.c
    ${SOURCES_DIR}/function.c
    ${SOURCES_DIR}/base.c
    ${SOURCES_DIR}/type.c
    ${SOURCES_DIR}/int.c
    ${SOURCES_DIR}/float.c
    ${SOURCES_DIR}/bool.c
    ${SOURCES_DIR}/table.c)

ADD_EXECUTABLE(duo
    ${SOURCES_DIR}/lexer.c
    ${SOURCES_DIR}/parser.c
    ${SOURCES_DIR}/main.c)

TARGET_LINK_LIBRARIES(duo
    duo01)