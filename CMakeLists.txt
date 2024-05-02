cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(alexandrescu_is_good)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED yes)
set(CMAKE_CXX_EXTENSIONS no)

# set warning level globabaly
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# lots of warnings and all warnings as errors
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)


# global assembly settings ###
if(WIN32)
  set(CMAKE_ASM_NASM_OBJECT_FORMAT win64)
else()
  set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
  set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
endif()


if (WIN32)
  # set startup project for VisualStudio
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT speed_tester)
endif()

# enable feature "folders" so that we can group targets in IDE
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# enable testing
enable_testing()

add_subdirectory(core)
