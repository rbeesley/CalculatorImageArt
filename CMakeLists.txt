CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)
PROJECT(png2rom VERSION 0.1.1)

# Test
#INCLUDE(CTest)
#ENABLE_TESTING()

# Target
SET(SRCS src/png2rom.c)
ADD_EXECUTABLE(png2rom ${SRCS})

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(LIBPNG REQUIRED libpng)

# Link
TARGET_LINK_LIBRARIES(png2rom ${LIBPNG_LIBRARIES})

# Package
#SET(CPACK_PROJECT_NAME ${PROJECT_NAME})
#SET(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#INCLUDE(CPack)
