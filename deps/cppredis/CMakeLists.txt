add_subdirectory(tacopie)

###
# variables
###
set(CPP_REDIS_INCLUDES includes tacopie/includes)


###
# includes
###
include_directories(${CPP_REDIS_INCLUDES})


###
# sources
###
set(CPP_REDIS_SRC_DIRS "sources"
        "sources/builders"
        "sources/core"
        "sources/misc"
        "sources/network"
        "includes/cpp_redis"
        "includes/cpp_redis/builders"
        "includes/cpp_redis/core"
        "includes/cpp_redis/misc"
        "includes/cpp_redis/network"
        )

foreach(dir ${CPP_REDIS_SRC_DIRS})
    # get directory sources and headers
    file(GLOB s_${dir} "${dir}/*.cpp")
    file(GLOB h_${dir} "${dir}/*.hpp")
    file(GLOB i_${dir} "${dir}/*.ipp")

    # set sources
    set(CPP_REDIS_SOURCES ${CPP_REDIS_SOURCES} ${s_${dir}} ${h_${dir}} ${i_${dir}})
endforeach()

###
# executable
###
add_library(cppredis ${CPP_REDIS_SOURCES})

target_link_libraries(cppredis pthread)
target_link_libraries(cppredis tacopie)

# __CPP_REDIS_READ_SIZE
if(READ_SIZE)
    set_target_properties(cppredis PROPERTIES COMPILE_DEFINITIONS "__CPP_REDIS_READ_SIZE=${READ_SIZE}")
endif(READ_SIZE)

# __CPP_REDIS_LOGGING_ENABLED
if(LOGGING_ENABLED)
    set_target_properties(cppredis PROPERTIES COMPILE_DEFINITIONS "__CPP_REDIS_LOGGING_ENABLED=${LOGGING_ENABLED}")
endif(LOGGING_ENABLED)

# __CPP_REDIS_USE_CUSTOM_TCP_CLIENT
if(USE_CUSTOM_TCP_CLIENT)
    set_target_properties(cppredis PROPERTIES COMPILE_DEFINITIONS "__CPP_REDIS_USE_CUSTOM_TCP_CLIENT=${USE_CUSTOM_TCP_CLIENT}")
endif(USE_CUSTOM_TCP_CLIENT)
