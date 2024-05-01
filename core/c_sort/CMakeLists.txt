project(c_sort CXX)

set(HEADER_FILES
  include/c_sort/bubble_sort.h
  include/c_sort/insertion_sort.h
  include/c_sort/selection_sort.h
  include/c_sort/quick_sort.h
)

set(SOURCE_FILES
  bubble_sort.cpp
  insertion_sort.cpp
  selection_sort.cpp
  quick_sort.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    include
)
