cmake_minimum_required(VERSION 4.0)
project(MyProject)

if(WIN32)
    # Windows
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_CXX_COMPILER "g++")
elseif(APPLE)
    # macOS
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_CXX_COMPILER "g++")
else()
    # Linux or other Unix-based systems
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_CXX_COMPILER "g++")
endif()

set(CMAKE_C_FLAGS "-Wall -g -Iinclude")
set(CMAKE_CXX_FLAGS "-Wall -g -Iinclude")

set(LDFLAGS "")


set(DEBUG_DIR "bin/debug")
set(RELEASE_DIR "bin/release")

set(RELEASE_CFLAGS "-Wall -O2 -Iinclude")

set(RELEASE_LDFLAGS "-s")


file(GLOB_RECURSE CPP_SRCS "src/*.cpp")

file(GLOB_RECURSE C_SRCS "src/*.c")

# Debug
add_executable(DEBUG ${C_SRCS} ${CPP_SRCS})
set_target_properties(DEBUG PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(DEBUG PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ../${DEBUG_DIR}
    RUNTIME_OUTPUT_NAME "main" 
)

target_link_options(DEBUG PRIVATE ${LDFLAGS})

# Release
add_executable(RELEASE ${C_SRCS} ${CPP_SRCS})
set_target_properties(RELEASE PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(RELEASE PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ../${RELEASE_DIR}
    RUNTIME_OUTPUT_NAME "main" 
)

target_link_options(RELEASE PRIVATE ${LDFLAGS} ${RELEASE_LDFLAGS})