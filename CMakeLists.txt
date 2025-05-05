cmake_minimum_required(VERSION 3.31)
project(warren)

set(CMAKE_CXX_STANDARD 20)

# SDL3 setup
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/dep/SDL3")
set(SDL3_DIR "${PROJECT_SOURCE_DIR}/dep/SDL3/cmake")

find_package(SDL3 REQUIRED)

add_subdirectory(${PROJECT_SOURCE_DIR}/dep/squirrel)


set(LOOSE_DEP_SRCS ${PROJECT_SOURCE_DIR}/dep/sqlite/sqlite3.c)

add_executable(warren main.cpp ${LOOSE_DEP_SRCS})
target_link_libraries(warren
        PRIVATE
        SDL3::SDL3-shared
        squirrel
)

target_include_directories(warren
        PRIVATE
        SDL3::Headers
)

add_custom_command(TARGET warren POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/dep/SDL3/lib/x64/SDL3.dll"      # <--this is in-file
        $<TARGET_FILE_DIR:warren>)                 # <--this is out-file path
