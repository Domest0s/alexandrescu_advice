project(job_runner)

set(HEADER_FILES
    jobs.hpp
)

set(SOURCE_FILES
    main.cpp
    jobs.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME}
    sort_alexandrescu
    vt100
    utils
)

