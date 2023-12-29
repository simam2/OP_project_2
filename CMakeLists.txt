cmake_minimum_required(VERSION 3.0.0)
project(OP VERSION 2.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(OP main.cpp)

# add_executable(TEST test.cpp)
# add_test(NAME TEST_CASE COMMAND TEST)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)