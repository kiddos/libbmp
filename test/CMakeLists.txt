add_executable(libbmp_test1 libbmp_test1.c)
target_link_libraries(libbmp_test1 PRIVATE libbmp)

add_executable(libbmp_test2 libbmp_test2.c)
target_link_libraries(libbmp_test2 PRIVATE libbmp)

add_executable(libbmp_test3 libbmp_test3.c)
target_link_libraries(libbmp_test3 PRIVATE libbmp)
