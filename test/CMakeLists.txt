set(RE_SOURCE_DIR ../src)
set(DEPS_DIR ../deps)

# include project
include_directories(${RE_SOURCE_DIR})
include_directories(${DEPS_DIR})
#include google test
include_directories(${DEPS_DIR}/googletest/include)
include_directories(${DEPS_DIR}/googletest)
# include redis
include_directories(${DEPS_DIR}/cppredis/includes)
include_directories(${DEPS_DIR}/cppredis/tacopie/includes)

add_executable(run_core_tests core_test.cpp postingsop_test.cpp)
add_executable(run_datastruct_tests datastruct_test.cpp)
add_executable(run_serialize_tests serialize_test.cpp)
add_executable(run_queryexpresser queryexpresser_test.cpp)

target_link_libraries(run_core_tests gtest gtest_main)
target_link_libraries(run_core_tests rake_engine)
target_link_libraries(run_core_tests cppredis)

target_link_libraries(run_datastruct_tests gtest gtest_main)
target_link_libraries(run_datastruct_tests rake_engine)

target_link_libraries(run_serialize_tests gtest gtest_main)

target_link_libraries(run_queryexpresser gtest gtest_main)
target_link_libraries(run_queryexpresser rake_engine)
target_link_libraries(run_queryexpresser cppredis)

add_executable(cpp_redis_tests cppredis_test.cpp)
target_link_libraries(cpp_redis_tests rake_engine)
target_link_libraries(cpp_redis_tests cppredis)
