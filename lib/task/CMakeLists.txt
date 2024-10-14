set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Task.cc")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Task.h")

add_library("LibTask" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_link_libraries("LibTask")

