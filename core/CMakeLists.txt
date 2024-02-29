# manage externals
include(FetchContent)

# add Gtest to the project
set(CMAKE_FOLDER ext)
FetchContent_Declare(
    googletest

    # Specify the commit you depend on and update it regularly.
    URL https://github.com/google/googletest/archive/e4fdb87e76b9fc4b01c54ad81aea19d6e994b994.zip

    # GIT_REPOSITORY https://github.com/google/googletest.git
    # GIT_TAG release-1.12.1
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
