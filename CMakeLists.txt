cmake_minimum_required(VERSION 3.15)

project(CustomLinkedList)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CustomLinkedList
    src/CustomLinkedList.cpp
)

target_include_directories(CustomLinkedList
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(CustomLinkedListExample
    examples/basic_usage.cpp
)

target_link_libraries(CustomLinkedListExample
    PRIVATE
        CustomLinkedList
)
add_executable(CustomLinkedListTests
    tests/test_custom_linked_list.cpp
)

target_link_libraries(CustomLinkedListTests
    PRIVATE
        CustomLinkedList
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif()