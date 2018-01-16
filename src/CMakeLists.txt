include_directories(.)
include_directories(../deps)
include_directories(../deps/cppredis/includes)
include_directories(../deps/cppredis/tacopie/includes)

set(CORE_SOURCE_FILES
        core/tokenizer.h core/tokenizerimpl.cpp core/tokenizerimpl.h
        core/termprocess.h core/termprocess.cpp)

set(RAKER_SOURCE_FILES
        raker/docindexer.cpp raker/docindexer.h)

set(SAKER_SOURCE_FILES
        saker/postingsop.h
        saker/queryexpresser/queryexpresser.h
        saker/queryexpresser/queryexpresser.cpp
        saker/postingsop.cpp)

set(COMMON_SOURCE_FILES
        common/deport/deport.h
        common/deport/redisdeport.cpp
        common/deport/redisdeport.h
        common/serializer.h
        common/factory/factory.h
        common/factory/deportfactory.h
        common/factory/factoryfactory.cpp
        common/factory/factoryfactory.h
        common/factory/tokenizerfactory.h
        common/taskwoker/worker.h
        common/taskwoker/task.h
        common/taskwoker/woker.cpp
        common/taskwoker/task.cpp
        common/integer2string.h common/string2wstring.h common/string2wstring.cpp)

set(DATA_SOURCE_FILES
        data/doc.h
        data/term.h
        data/postingsmap.h
        data/map.h
        data/wrappedstlmap.hpp
        data/taskqueue.h
        data/redistaskqueue.cpp
        data/redistaskqueue.h
        common/taskwoker/breakdocblocktask.cpp
        common/taskwoker/breakdocblocktask.h
        common/taskwoker/sortandmergetempintodicttask.cpp
        common/taskwoker/sortandmergetempintodicttask.h
        common/taskwoker/queryexpresstask.cpp common/taskwoker/queryexpresstask.h common/taskwoker/response.h common/taskwoker/response.cpp common/log.h "common/log.cpp" core/wilermatcher.cpp core/wilermatcher.h)

add_library(rake_engine STATIC
        ${COMMON_SOURCE_FILES}
        ${CORE_SOURCE_FILES}
        ${DATA_SOURCE_FILES}
        ${RAKER_SOURCE_FILES}
        ${SAKER_SOURCE_FILES}
        common/config.h main.cpp)

add_executable(rake_engine_exec main.cpp)
target_link_libraries(rake_engine_exec rake_engine)
target_link_libraries(rake_engine_exec cppredis)
