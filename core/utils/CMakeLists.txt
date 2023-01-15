project(utils)

set(HEADER_FILES
    include/rnum_generator.hpp
)

add_library(${PROJECT_NAME} INTERFACE ${HEADER_FILES})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
