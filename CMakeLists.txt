cmake_minimum_required(VERSION 3.18)

project(AlexandrescuIsGood)

# set warning level globabaly
if (MSVC)
    add_compile_options(/W4)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

if (WIN32)
  # set startup project for VisualStudio
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT app)
endif()

add_subdirectory(app)
