set(target app_${PROJECT_NAME})

file(GLOB HEADERS "include/*.hpp")
file(GLOB SOURCES "src/*.cpp")

add_executable(${target} ${SOURCES} ${HEADERS})
if (UNIX)
  target_link_libraries(${target} ${app} ${CMAKE_THREAD_LIBS_INIT})
endif (UNIX)
target_link_libraries(${target} ${app} ${LIBRARY_DEPS} )
