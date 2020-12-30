cmake_minimum_required(VERSION 3.0.0)
project(png2rom VERSION 0.1.0)

#include(CTest)
#enable_testing()

#Target
set(SRCS png2rom.c)
ADD_EXECUTABLE(png2rom ${SRCS})

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(LIBPNG REQUIRED libpng)

INCLUDE_DIRECTORIES(${LIBPNG_INCLUDE_DIRS})
target_link_libraries(png2rom ${LIBPNG_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
