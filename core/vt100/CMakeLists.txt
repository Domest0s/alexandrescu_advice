project(vt100)

set(HEADER_FILES
    include/vt100.h
)

set(SOURCE_FILES
    vt100.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
)
