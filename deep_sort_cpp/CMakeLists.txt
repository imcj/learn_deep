cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -E -dD")

project(deep_sort)

include(FetchContent)

FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG        3.3.7
)

FetchContent_GetProperties(eigen)
if(NOT eigen_POPULATED)
  FetchContent_Populate(eigen)
  add_subdirectory(${eigen_SOURCE_DIR} ${eigen_BINARY_DIR})
endif()


# the project setup

include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_DIR)

add_library(deep_sort ${SRC_DIR})

link_libraries(
  deep_sort
  eigen
)

target_include_directories(deep_sort PRIVATE ${eigen_SOURCE_DIR})

#c test
enable_testing()

add_executable(
  deep_sort_test
  ${PROJECT_SOURCE_DIR}/src/iou_test.cc
)

link_libraries(
  deep_sort_test
  deep_sort
)

add_test(NAME deep_sort_test COMMAND deep_sort_test)

# GoogleTest requires at least C++14

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

# enable_testing()


# add_executable(
#   deep_sort_test
#   ${PROJECT_SOURCE_DIR}/src/iou_test.cc
# )

# message("Google test source dir: " ${googletest_SOURCE_DIR})


# target_link_libraries(
#   deep_sort_test
#   # gtest
#   # gtest_main
#   GTest::gtest_main
#   pthread
# )

# target_include_directories(deep_sort_test PRIVATE ${googletest_SOURCE_DIR}/googletest/include)

# include(GoogleTest)
# gtest_discover_tests(deep_sort_test)


# message("Include directories:")
# get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
# foreach(dir ${dirs})
#     message(STATUS "  ${dir}")
# endforeach()

