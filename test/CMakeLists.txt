set(TARGET ${CMAKE_SOURCE_DIR}/src/bmp.c ${CMAKE_SOURCE_DIR}/src/msg.c)

add_executable(libbmp_test1 libbmp_test1.c ${TARGET})

add_executable(libbmp_test2 libbmp_test2.c ${TARGET})

add_executable(libbmp_test3 libbmp_test3.c ${TARGET})
