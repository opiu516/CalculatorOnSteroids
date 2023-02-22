cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(tutorial VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  test_thing
  test/tempTest.cpp
)
target_link_libraries(
  test_thing
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_thing)

add_executable(
    client
    src/client/clientTemp.cpp
)

add_executable(
    server
    src/server/serverTemp.cpp
)

add_executable(
    debug
    src/messageDebug.cpp
)

target_include_directories(debug PUBLIC
  lib/spdlog/include
)

target_include_directories(server PUBLIC
  lib/spdlog/include
)

target_include_directories(client PUBLIC
  lib/spdlog/include
)