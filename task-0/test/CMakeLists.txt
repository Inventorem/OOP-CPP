include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
set(PROJECT_TEST_NAME "big_int_test")

add_executable(
        ${PROJECT_TEST_NAME}
        big_int_tests.cc
)

target_link_libraries(
        ${PROJECT_TEST_NAME}
        GTest::gtest
        GTest::gtest_main
        bigint
        gcov
)
include(GoogleTest)
gtest_discover_tests(
        ${PROJECT_TEST_NAME}
)
