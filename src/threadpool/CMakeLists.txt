
aux_source_directory(. THREADPOOL_SRCS_LIST)

add_library(luothreadpool ${THREADPOOL_SRCS_LIST})
target_link_libraries(luothreadpool pthread)
