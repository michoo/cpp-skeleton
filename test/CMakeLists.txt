cmake_minimum_required(VERSION 3.5)

project(Example)

include(CTest)


# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(DownloadProject.cmake)
download_project(PROJ                googletest
        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG             master
        UPDATE_DISCONNECTED 1
        QUIET
        )

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})


# Trivial example using gtest and gmock

include_directories(${PROJECT_INCLUDES} )

#thread tests
add_executable(runThreadUnitTests SimpleTest.cpp)
target_link_libraries(runThreadUnitTests gtest gtest_main gmock ${PROJECT_LIBRARIES} opencv-tuto-core)

add_test(
        NAME runThreadUnitTests
        COMMAND runThreadUnitTests
)

#postgresql
add_executable(runPostgresqlUnitTests PostgresqlTest.cpp)
target_link_libraries(runPostgresqlUnitTests gtest gtest_main gmock ${PROJECT_LIBRARIES} opencv-tuto-core)

add_test(
        NAME runPostgresqlUnitTests
        COMMAND runPostgresqlUnitTests
)

#serial
add_executable(runSerialUnitTests SerialTest.cpp)
target_link_libraries(runSerialUnitTests gtest gtest_main gmock ${PROJECT_LIBRARIES} opencv-tuto-core)

add_test(
        NAME runSerialUnitTests
        COMMAND runSerialUnitTests
)