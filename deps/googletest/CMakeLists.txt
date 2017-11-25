INCLUDE_DIRECTORIES(./ include)
ADD_LIBRARY(gtest STATIC src/gtest-all.cc)
ADD_LIBRARY(gtest_main STATIC src/gtest_main.cc)

if(NOT MSVC)
    TARGET_LINK_LIBRARIES(gtest pthread)
endif()
