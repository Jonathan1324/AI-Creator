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
file(GLOB_RECURSE CPP_HEADERS "src/*.hpp")

file(GLOB_RECURSE C_SRCS "src/*.c")
file(GLOB_RECURSE C_HEADERS "src/*.h")


file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/c)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/cpp)


set(OBJECT_FILES "")

function(get_obj_path out_var src_file type_folder)
    file(RELATIVE_PATH rel_path "${CMAKE_SOURCE_DIR}/src" "${src_file}")
    string(REPLACE ".cpp" ".o" rel_path "${rel_path}")
    string(REPLACE ".c"   ".o" rel_path "${rel_path}")
    set(${out_var} "${CMAKE_BINARY_DIR}/${type_folder}/${rel_path}" PARENT_SCOPE)
endfunction()

# C Files
foreach(src ${C_SRCS})
    get_obj_path(obj_path ${src} "c")
    get_filename_component(obj_dir ${obj_path} DIRECTORY)
    file(MAKE_DIRECTORY ${obj_dir})

    add_custom_command(
        OUTPUT ${obj_path}
        COMMAND ${CMAKE_C_COMPILER} -c ${src} -o ${obj_path}
        DEPENDS ${src} ${C_HEADERS}
    )
    list(APPEND OBJECT_FILES ${obj_path})
endforeach()

# C++ Files
foreach(src ${CPP_SRCS})
    get_obj_path(obj_path ${src} "cpp")
    get_filename_component(obj_dir ${obj_path} DIRECTORY)
    file(MAKE_DIRECTORY ${obj_dir})

    add_custom_command(
        OUTPUT ${obj_path}
        COMMAND ${CMAKE_CXX_COMPILER} -c ${src} -o ${obj_path}
        DEPENDS ${src} ${CPP_HEADERS}
    )
    list(APPEND OBJECT_FILES ${obj_path})
endforeach()

# Debug
add_executable(DEBUG ${OBJECT_FILES})
set_target_properties(DEBUG PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(DEBUG PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ../${DEBUG_DIR}
    RUNTIME_OUTPUT_NAME "main" 
)

target_link_options(DEBUG PRIVATE ${LDFLAGS})

# Release
add_executable(RELEASE ${OBJECT_FILES})
set_target_properties(RELEASE PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(RELEASE PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ../${RELEASE_DIR}
    RUNTIME_OUTPUT_NAME "main" 
)

target_link_options(RELEASE PRIVATE ${LDFLAGS} ${RELEASE_LDFLAGS})