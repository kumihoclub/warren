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
        sqlite
        URL https://sqlite.org/2025/sqlite-amalgamation-3490200.zip
        EXCLUDE_FROM_ALL
)

FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.8.1
        GIT_PROGRESS TRUE
        EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(SDL3)
FetchContent_MakeAvailable(squirrel)
FetchContent_MakeAvailable(sqlite)
FetchContent_MakeAvailable(catch2)

message("${SQLITE3_LIBRARIES}")

set(SRCS
        drive/src/dbio.cpp
        drive/dbio.h
        drive/data.h
        uid.h

)

add_executable(warren
        main.cpp
        ${sqlite_SOURCE_DIR}/sqlite3.c
        ${SRCS}
)
target_link_libraries(warren
        PRIVATE
        SDL3::SDL3-shared
        squirrel::squirrel
)

target_include_directories(warren
        PRIVATE
        SDL3::Headers
        squirrel::Headers
        ${sqlite_SOURCE_DIR}
)

add_custom_command(TARGET warren POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE_DIR:SDL3-shared>/SDL3.dll
        $<TARGET_FILE_DIR:warren>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE_DIR:squirrel>/squirrel.dll
        $<TARGET_FILE_DIR:warren>
)
