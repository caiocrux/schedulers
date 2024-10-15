set(LIB_DL_NAME "LibDL")
set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/deadlineMonotonic.cc")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/deadlineMonotonic.h")
set(LIBRARY_INCLUDES "./")

add_library(${LIB_DL_NAME} STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${LIB_DL_NAME}  PUBLIC ${LIBRARY_INCLUDES} )
target_link_libraries(${LIB_DL_NAME} PRIVATE LibTask LibSH)
