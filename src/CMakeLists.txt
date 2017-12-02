include_directories(.)
include_directories(../deps)
include_directories(../deps/cppredis/includes)
include_directories(../deps/cppredis/tacopie/includes)

set(CORE_SOURCE_FILES
        core/doc2term.cpp core/doc2term.h
        core/normalizer.h core/normalizerimpl.cpp core/normalizerimpl.h
        core/tokenizer.h core/tokenizerimpl.cpp core/tokenizerimpl.h
        core/term2posting.h core/term2posting.cpp
        )

set(SAKER_SOURCE_FILES
        saker/postingsop.hpp
        saker/queryexpresser/queryexpresser.h saker/queryexpresser/queryexpresser.cpp
        saker/queryexpresser/statement.h
        saker/queryexpresser/binarystatement.h
        saker/queryexpresser/bsconjunction.cpp
        saker/queryexpresser/bsconjunction.h
        saker/queryexpresser/bsintersect.cpp
        saker/queryexpresser/bsintersect.h
        saker/queryexpresser/bsexclude.cpp
        saker/queryexpresser/bsexclude.h
        saker/queryexpresser/bsfetchpostings.cpp
        saker/queryexpresser/bsfetchpostings.h
        )

set(COMMON_SOURCE_FILES
        common/deport.h
        common/redisdeport.cpp
        common/redisdeport.h
        common/serializer.h
        common/factory/factory.h common/factory/deportfactory.h common/factory/factoryfactory.cpp common/factory/factoryfactory.h)

set(DATA_SOURCE_FILES
        data/doc.h
        data/term.h
        data/postingsmap.h
        data/map.h
        data/wrappedstlmap.hpp
        )

add_library(rake_engine STATIC
        ${CORE_SOURCE_FILES}
        ${DATA_SOURCE_FILES}
        ${SAKER_SOURCE_FILES}
        ${COMMON_SOURCE_FILES}
        )
