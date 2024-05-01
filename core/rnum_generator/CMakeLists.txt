project(rnum_generator CXX)

set(HEADER_FILES
  include/rnum_generator/generator.h
)

set(SOURCE_FILES
  generator.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} 
  PUBLIC
    include
)
