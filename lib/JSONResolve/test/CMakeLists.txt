CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

INCLUDE(ExternalProject)
EXTERNALPROJECT_ADD(gtest PREFIX gtest
                    SVN_REPOSITORY http://googletest.googlecode.com/svn/tags/release-1.7.0
                    INSTALL_COMMAND "" )

PROJECT(mjsontest CXX)

INCLUDE_DIRECTORIES(SYSTEM ./gtest/src/gtest/include ../include)

FILE(GLOB_RECURSE sauce "./src/*.cpp" "../src/*.cpp")
FILE(GLOB_RECURSE headers "./src/*.hpp" "../src/*.hpp" "../include/*.hpp")

ADD_EXECUTABLE(mjsontest  ${sauce} ${headers})

IF(WIN32)
    SET(ADDITIONAL_LINK_LIBRARIES "")
ELSE()
    SET(ADDITIONAL_LINK_LIBRARIES pthread)
ENDIF()

TARGET_LINK_LIBRARIES(mjsontest
                      ${CMAKE_SOURCE_DIR}/gtest/src/gtest-build/libgtest_main.a
                      ${CMAKE_SOURCE_DIR}/gtest/src/gtest-build/libgtest.a
                      ${ADDITIONAL_LINK_LIBRARIES}
#                      ${CMAKE_SOURCE_DIR}/../lib/libmjson.a)
)
