set(TACOPIE_INCLUDES includes)

###
# includes
###
include_directories(${TACOPIE_INCLUDES})

###
# sources
###
set(SRC_DIRS
        "sources"
        "sources/network"
        "sources/network/common"
        "sources/utils"
        "includes/tacopie"
        "includes/tacopie/network"
        "includes/tacopie/utils"
        "sources/network/unix"
        )

foreach(dir ${SRC_DIRS})
    # get directory sources and headers
    file(GLOB s_${dir} "${dir}/*.cpp")
    file(GLOB h_${dir} "${dir}/*.hpp")
    file(GLOB i_${dir} "${dir}/*.ipp")

    # set sources
    set(SOURCES ${SOURCES} ${s_${dir}} ${h_${dir}} ${i_${dir}})
endforeach()


###
# executable
###
add_library(tacopie ${SOURCES})

target_link_libraries(tacopie pthread)

# __TACOPIE_LOGGING_ENABLED
IF (LOGGING_ENABLED)
    set_target_properties(tacopie PROPERTIES COMPILE_DEFINITIONS "__TACOPIE_LOGGING_ENABLED=${LOGGING_ENABLED}")
ENDIF (LOGGING_ENABLED)

# __TACOPIE_CONNECTION_QUEUE_SIZE
IF (CONNECTION_QUEUE_SIZE)
    set_target_properties(tacopie PROPERTIES COMPILE_DEFINITIONS "__TACOPIE_CONNECTION_QUEUE_SIZE=${CONNECTION_QUEUE_SIZE}")
ENDIF (CONNECTION_QUEUE_SIZE)

#__TACOPIE_IO_SERVICE_NB_WORKERS
IF (IO_SERVICE_NB_WORKERS)
    set_target_properties(tacopie PROPERTIES COMPILE_DEFINITIONS "__TACOPIE_IO_SERVICE_NB_WORKERS=${IO_SERVICE_NB_WORKERS}")
ENDIF(IO_SERVICE_NB_WORKERS)

#__TACOPIE_TIMEOUT
IF (SELECT_TIMEOUT)
    set_target_properties(tacopie PROPERTIES COMPILE_DEFINITIONS "__TACOPIE_TIMEOUT=${SELECT_TIMEOUT}")
ENDIF(SELECT_TIMEOUT)
