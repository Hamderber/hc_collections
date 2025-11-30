cmake_minimum_required(VERSION 3.10)
project(hc_collections VERSION 0.1.0 LANGUAGES C)

function(hc_enable_strict_warnings target)
    if (MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_library(hc_collections STATIC ${SRC_FILES})

target_include_directories(hc_collections PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

hc_enable_strict_warnings(hc_collections)

include(CTest)
enable_testing()

file(GLOB TEST_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.c"
)

set(TEST_EXECUTABLES "")

foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_link_libraries(${test_name} PRIVATE hc_collections)
    hc_enable_strict_warnings(${test_name})
    add_test(NAME ${test_name} COMMAND ${test_name})
    list(APPEND TEST_EXECUTABLES ${test_name})
endforeach()

add_custom_target(check ALL
    COMMAND ${CMAKE_CTEST_COMMAND}
            --output-on-failure
            --no-tests=ignore
            -C $<CONFIG>
    DEPENDS ${TEST_EXECUTABLES}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
