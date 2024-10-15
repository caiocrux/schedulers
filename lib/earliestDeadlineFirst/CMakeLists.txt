set(LIB_EDF_NAME "LibEDF")
set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/earliestDeadlineFirst.cc")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/earliestDeadlineFirst.h")
set(LIBRARY_INCLUDES "./")

add_library(${LIB_EDF_NAME} STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${LIB_EDF_NAME}  PUBLIC ${LIBRARY_INCLUDES} )
target_link_libraries(${LIB_EDF_NAME} PRIVATE LibTask LibSH)
