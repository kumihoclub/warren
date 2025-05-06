cmake_minimum_required(VERSION 3.31)
project(warren)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INSTALL_LOCAL_ONLY TRUE)

include(FetchContent)

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.12
        GIT_PROGRESS TRUE
        EXCLUDE_FROM_ALL
)

FetchContent_Declare(
        squirrel
        GIT_REPOSITORY https://github.com/albertodemichelis/squirrel.git
        GIT_TAG v3.2
        GIT_PROGRESS TRUE
        EXCLUDE_FROM_ALL
)

FetchContent_Declare(
        leveldb
        GIT_REPOSITORY https://github.com/google/leveldb.git
        GIT_TAG main
        GIT_PROGRESS TRUE
        EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(SDL3)
FetchContent_MakeAvailable(squirrel)
FetchContent_MakeAvailable(leveldb)

#find_package(SDL3 REQUIRED)
#
#add_subdirectory(${PROJECT_SOURCE_DIR}/dep/squirrel)
#
#set(LOOSE_DEP_SRCS ${PROJECT_SOURCE_DIR}/dep/sqlite/sqlite3.c)

add_executable(warren main.cpp)#${LOOSE_DEP_SRCS})
target_link_libraries(warren
        PRIVATE
        SDL3::SDL3-shared
        squirrel::squirrel
        leveldb
)

target_include_directories(warren
        PRIVATE
        SDL3::Headers
        squirrel::Headers
        leveldb::Headers
)

add_custom_command(TARGET warren POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:SDL3-shared>/SDL3.dll"
        $<TARGET_FILE_DIR:warren>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:squirrel>/squirrel.dll"
        $<TARGET_FILE_DIR:warren>
)
