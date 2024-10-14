set(LIB_LL_NAME "LibLL")
set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/leastLaxity.cc")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/leastLaxity.h")
set(LIBRARY_INCLUDES "./")

add_library(${LIB_LL_NAME} STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${LIB_LL_NAME}  PUBLIC ${LIBRARY_INCLUDES} )
target_link_libraries(${LIB_LL_NAME} PRIVATE LibTask)
