#add_subdirectory(${PROJECT_DIR}/libs/gtest*)

add_executable(heap_repl heap_repl.cpp)

add_executable(run_heap_tests heap_tests.cpp)
target_link_libraries(run_heap_tests gtest gtest_main) 
add_test(heap_tests run_heap_tests)
