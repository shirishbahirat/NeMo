cmake_minimum_required(VERSION 3.0)
project(TN_JSON_2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(model_lib_src src/tn_json_parser.cpp include/tn_json_parser.hh)
set(model_bin_src main.cpp)

add_library(TN_json_lib ${model_lib_src})
add_library(TN_json_lib::TN_json_lib ALIAS TN_json_lib)


#### Options and compile-time optimization options
option(BUILD_JSONCPP "Build bundled JSONCPP? Otherwise will use system installed library." )
option(TN_READER_OMP "Enable OpenMP for reader loops?")
option(TN_READER_TEST "Enable testing of TN Reader? (debug mode)" ON )



######## Standards, configs, openmp settings #########
if(TN_READER_OMP)
    find_package(OpenMP)
    if (OPENMP_FOUND)
        message(STATUS "Found OpenMP")
        add_definitions(-DUSE_OMP=1)

        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

    endif()
    message(STATUS "Did not find OpenMP - not enabled.")
endif()

if(TN_READER_TEST)
    add_definitions(-DSRC_ROOT="${CMAKE_CURRENT_SOURCE_DIR}")
    add_definitions(-DDEBUG)
    set(DEBUG 1)
endif()

### BUILD NEEDS MPI, CMAKE, ROSS files.
INCLUDE_DIRECTORIES(
        ${MPI_INCLUDE_PATH}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${ROSS_SOURCE_DIR}
        ${ROSS_BINARY_DIR}
)
if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    #release optimization flags
        message("adding optimization flags")
        if(ARCH STREQUAL "ppc64le" OR ARCH STREQUAL "bgq")
            message("POWER architecture detected")
            #bgq settings
        endif()
endif()

target_include_directories(TN_json_lib
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_features(TN_json_lib PRIVATE cxx_std_11)

message("----------- trying to find Jsoncpp-------------")
#set(BUILD_JSONCPP CACHE FLAG FALSE "Build bundled JSONCPP? Otherwise will use system installed library.")


if(BUILD_JSONCPP)
    #set(model_lib_src ${model_lib_src} lib/jsoncpp.cpp lib/json/json.h lib/json/json-forwards.h)
        target_include_directories(TN_json_lib
                PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/lib)
    message("Added jsonCPP sources.")
    set_target_properties(TN_json_lib DBUILDJSON=1)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(JSONCPP jsoncpp)
    link_libraries(${JSONCPP_LIBRARIES})
#    find_path(JSONCPP_INCLUDE_DIR
#            NAMES json.h
#            PATHS ${JSON_CPP_INCLUDE_DIRS}
#            PATH_SUFFIXES json)
    message("Result: ${JSONCPP_LIBRARIES} - ${JSONCPP_INCLUDE_DIRS}")
        add_library(jsoncpp::jsoncpp INTERFACE IMPORTED)
        set_target_properties(jsoncpp::jsoncpp PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${JSONCPP_INCLUDE_DIRS}")
    set_target_properties(TN_json_lib PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${JSONCPP_INCLUDE_DIRS}")
        target_include_directories(TN_json_lib
                PRIVATE
                "${JSONCPP_INCLUDE_DIRS}")
        target_link_libraries(TN_json_lib ${JSONCPP_LIBRARIES})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${JSONCPP_INCLUDE_DIRS}")

    #add_dependencies(TN_json_lib JSONCPP)
endif()




add_executable(ModelReader2 main.cpp)
add_dependencies(ModelReader2 TN_json_lib)
target_link_libraries(TN_json_lib ROSS m)
target_link_libraries(ModelReader2 ModelReaderLib)


######### SET UP TET FILES ############
if(TN_READER_TEST)

        set(TEST_OUT_DIR  ${CMAKE_BINARY_DIR}/bin/tests)
        message("Saving test files to ${TEST_OUT_DIR} ")
    configure_file(tests/th_small_test.json ${TEST_OUT_DIR}/th_small_test.json COPYONLY )
    configure_file(tests/th_corelet_net.json ${TEST_OUT_DIR}/th_corelet_net.json COPYONLY )
    configure_file(tests/BootCampExample11.json ${TEST_OUT_DIR}/BootCampExample11.json COPYONLY )
endif()
########### LIB EXPORT OPTIONS
#set_target_properties(TN_json_lib PROPERTIES EXPORT_NAME TN_json_lib)
#
#include(GNUInstallDirs)
#set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/tn_json_lib)
#
#
#message("Paths set to: ${CMAKE_INSTALL_NAME_DIR}")
#
#install(TARGETS TN_json_lib
#        EXPORT TN_json_lib-targets
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        )
#
#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
#
#install(EXPORT TN_json_lib-targets
#        FILE
#        TN_json_libTargets.cmake
#        NAMESPACE
#        TN_json_lib::
#        DESTINATION
#        ${INSTALL_CONFIGDIR}
#        )
