project(app)

set(map_example_files
  resourses/mission01.txt
  resourses/mission02.txt
  resourses/mission03.txt
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/resourses
  PREFIX resourses
  FILES ${map_example_files}
)
set(SOURCE_FILES
  src/main.cpp
  src/MapReader.h
  src/vt100.h
  src/resourcePath.h.in
)

add_executable(${PROJECT_NAME}
  ${SOURCE_FILES}
  ${map_example_files}
)


set(MAP_FILES_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/resourses)
configure_file(src/resourcePath.h.in resourcePath.h @ONLY)
target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

