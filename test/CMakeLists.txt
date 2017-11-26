set(RE_SOURCE_DIR ../src)
set(DEPS_DIR ../deps)

include_directories(${RE_SOURCE_DIR})
include_directories(${DEPS_DIR})
include_directories(${DEPS_DIR}/googletest/include ${DEPS_DIR}/googletest)

add_executable(run_doc2term_tests core/doc2term_test.cpp)
add_executable(run_datastruct_tests data/datastruct_test.cpp)

target_link_libraries(run_doc2term_tests gtest gtest_main)
target_link_libraries(run_doc2term_tests lib_rake_engine)

target_link_libraries(run_datastruct_tests gtest gtest_main)
target_link_libraries(run_datastruct_tests lib_rake_engine)
