include_directories(../deps)

set(CORE_SOURCE_FILES
        core/doc2term.cpp core/doc2term.h
        core/normalizer.h core/normalizerimpl.cpp core/normalizerimpl.h
        core/tokenizer.h core/tokenizerimpl.cpp core/tokenizerimpl.h core/term2posting.h core/term2posting.cpp)

set(DATA_SOURCE_FILES
        data/doc.h
        data/term.h
        data/postingsmap.h
        data/map.h
        data/wrappedstlmap.hpp)

add_library(lib_rake_engine STATIC ${CORE_SOURCE_FILES} ${DATA_SOURCE_FILES})
