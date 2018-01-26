cmake_minimum_required(VERSION 3.9)
project(Tutorial C)

set(CMAKE_C_STANDARD 11)
find_package(GSL REQUIRED)
### GSL ######################################
FIND_LIBRARY(GSL_LIBRARIES gsl
        PATHS
        /usr/lib
        /usr/local/lib
        )
FIND_LIBRARY (GSL_CBLAS_LIBRARIES gslcblas
        PATHS
        /usr/lib
        /usr/local/lib
        )
FIND_PATH (GSL_INCLUDE_DIR gsl_multimin.h
        /usr/include/gsl
        /usr/local/include/gsl
        )
FIND_PROGRAM (GSL_CONFIG gsl-config
        /usr/bin
        /usr/local/bin
        )
IF (GSL_CONFIG)
    EXEC_PROGRAM (${GSL_CONFIG} ARGS "--version" OUTPUT_VARIABLE gsl_version)
    SET (GSL_VERSION ${gsl_version} CACHE STRING "GNU Scientific Library Version")
ENDIF (GSL_CONFIG)
IF (GSL_LIBRARIES AND GSL_CBLAS_LIBRARIES AND GSL_INCLUDE_DIR)
    SET (GSL_FOUND TRUE)
ELSE (GSL_LIBRARIES AND GSL_CBLAS_LIBRARIES AND GSL_INCLUDE_DIR)
    SET (GSL_FOUND FALSE)
ENDIF (GSL_LIBRARIES AND GSL_CBLAS_LIBRARIES AND GSL_INCLUDE_DIR)

IF (GSL_FOUND)
    MESSAGE (STATUS "Found GNU Scientific Library ${GSL_VERSION}: ${GSL_INCLUDE_DIR} ${GSL_LIBRARIES};${GSL_CBLAS_LIBRARIES}")
    add_definitions (-DHAVE_GSL=1)
    # TODO : set version ?
    add_definitions (-DGSL_VERSION=GSL_VERSION)
ELSE (GSL_FOUND)
    MESSAGE (FATAL_ERROR "GNU Scientific Library not found.")
ENDIF (GSL_FOUND)


add_executable(Tutorial main.c)
add_executable(Tutorial2 main1.c)
target_link_libraries( Tutorial ${GSL_LIBRARIES})