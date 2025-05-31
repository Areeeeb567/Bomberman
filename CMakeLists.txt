cmake_minimum_required(VERSION 3.25)
project(cmake-sfml-project-master)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_subdirectory(src/Project_lib)

add_executable(cmake-sfml-project-master src/main.cpp
        src/Project_lib/Game.cpp
        src/Project_lib/Game.h
        src/Project_lib/GameEvent.cpp
        src/Project_lib/GameEvent.h
        src/Project_lib/Menu.cpp
        src/Project_lib/Menu.h)
target_link_libraries(cmake-sfml-project-master PRIVATE Project_lib sfml-graphics sfml-audio)
target_compile_features(cmake-sfml-project-master PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
            TARGET cmake-sfml-project-master
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:cmake-sfml-project-master>
            VERBATIM)
endif()

install(TARGETS cmake-sfml-project-master)
