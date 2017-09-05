cmake_minimum_required (VERSION 2.8)
project (WaferProb)
# The version number.
set (WaferProb_VERSION_MAJOR 1)
set (WaferProb_VERSION_MINOR 0)

# what for?
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8)
        message(FATAL_ERROR "GCC version must be at least 4.8!")
    endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.2)
        message(FATAL_ERROR "Clang version must be at least 3.2!")
    endif()
else()
    message(WARNING "You are using an unsupported compiler! Compilation has only been tested with Clang and GCC.")
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
add_compile_options(-g)
else()
add_compile_options(-O4)
endif()
add_compile_options(-Wfatal-errors)
add_compile_options(-Wno-deprecated)
# add_compile_options(-Wc++11-extensions)
# add_compile_options(-std=c++11)

# add libraries
list(APPEND libs Galil Zaber WaferProb)
foreach(lib ${libs})
include_directories(lib${lib}/include)
file(GLOB SrcFiles lib${lib}/*.c*)
list(APPEND LibSrcFiles ${SrcFiles})
endforeach()
add_library(WaferProb STATIC ${LibSrcFiles})

# add executables
file(GLOB tools tools/*.c*)
foreach(target ${tools})
get_filename_component(execname ${target} NAME_WE)
get_filename_component(srcfile ${target} NAME)
add_executable(${execname} tools/${srcfile})
add_dependencies(${execname} WaferProb)
set_target_properties(${execname} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${execname} WaferProb)
endforeach()

