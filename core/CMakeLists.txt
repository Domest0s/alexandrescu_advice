# manage externals
include(FetchContent)

# add Gtest to the project
set(CMAKE_FOLDER ext)
FetchContent_Declare(
    googletest
    # Specify the commit you depend on and update it regularly.
    URL https://github.com/google/googletest/archive/e4fdb87e76b9fc4b01c54ad81aea19d6e994b994.zip

    # otherwise specify a git tag (it takes longer)
    # GIT_REPOSITORY https://github.com/google/googletest.git
    # GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# the convention is that imported targets are comming in a namespace.
# Here we build GTest ourself and targets are comming in a naked form.
# To smooth the transition to the "package managed" solution, we can
# create namespaced aliases.
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

set(CMAKE_FOLDER)


# projects
add_subdirectory(vt100)

add_subdirectory(rnum_generator)

# add_subdirectory(asm_sort)
# add_subdirectory(asm_sort_test)
add_subdirectory(c_sort)
add_subdirectory(c_sort_test)

add_subdirectory(speed_tester)


# add_subdirectory(utils)

# add_subdirectory(sort_alexandrescu)
# add_subdirectory(sort_alexandrescu_test)
# add_subdirectory(job_runner)
# add_subdirectory(app)
