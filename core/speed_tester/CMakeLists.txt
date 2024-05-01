project(speed_tester LANGUAGES CXX)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

set(HEADER_FILES
  vt100.hpp
  sort_jobs.hpp
)

set(SOURCE_FILES
  main.cpp
  sort_jobs.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    # asm_sort
    c_sort
    rnum_generator
    Threads::Threads
)
