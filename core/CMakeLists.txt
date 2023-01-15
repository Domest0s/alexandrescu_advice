# manage externals
include(FetchContent)

# add Gtest to the project
set(CMAKE_FOLDER ext)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
set(CMAKE_FOLDER)

# enumerate projects
add_subdirectory(vt100)
add_subdirectory(utils)

add_subdirectory(sort_alexandrescu)
add_subdirectory(sort_alexandrescu_test)
add_subdirectory(job_runner)
add_subdirectory(app)
