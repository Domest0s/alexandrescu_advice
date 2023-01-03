project(sort_alexandrescu)

set(HEADER_FILES
  include/sorter.h
)

set(SOURCE_FILES
  sorter.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
)

