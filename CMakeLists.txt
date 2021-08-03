cmake_minimum_required(VERSION 3.18)

project(AlexandrescuIsGood)

if (WIN32)
  # set startup project for VisualStudio
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT app)
endif()

add_subdirectory(app)
