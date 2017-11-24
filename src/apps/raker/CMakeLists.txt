include_directories(../../../deps)

set(SOURCE_FILES main.cpp ../../common/taskwoker/task.h ../../common/data/doc.h ../../common/taskwoker/worker.h ../../core/doctokenizer.h ../../core/doctokenizerimpl.cpp ../../core/doctokenizerimpl.h ../../common/data/token.h)
add_executable(hello_world ${SOURCE_FILES})