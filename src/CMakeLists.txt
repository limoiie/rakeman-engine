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
        saker/postingsop.hpp
        saker/queryexpresser/queryexpresser.h
        saker/queryexpresser/queryexpresser.cpp
        )

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
        common/taskwoker/woker.cpp common/taskwoker/task.cpp)

set(DATA_SOURCE_FILES
        data/doc.h
        data/term.h
        data/postingsmap.h
        data/map.h
        data/wrappedstlmap.hpp
        data/taskqueue.h data/redistaskqueue.cpp data/redistaskqueue.h common/taskwoker/breakdocblocktask.cpp common/taskwoker/breakdocblocktask.h common/taskwoker/sortunsortedpostinglisttask.cpp common/taskwoker/sortunsortedpostinglisttask.h)

add_library(rake_engine STATIC
        ${CORE_SOURCE_FILES}
        ${DATA_SOURCE_FILES}
        ${COMMON_SOURCE_FILES}
        ${RAKER_SOURCE_FILES}
        ${SAKER_SOURCE_FILES}
        )
