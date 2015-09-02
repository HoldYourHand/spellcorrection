add_subdirectory(net)
add_subdirectory(threadpool)

set(MAIN_SRCS_LIST
	conf.cc
	main.cc
	MyDict.cc)

#find_path(PTHREAD_INCLUDE_DIR pthread.h)
#find_library(PTHREAD_LIBRARY NAMES pthread)
#if(PTHREAD_LIBRARY AND PTHREAD_INCLUDE_DIR)
#	include_directories(${PTHREAD_INCLUDE_DIR})
#	message(STATUS ${PTHREAD_INCLUDE_DIR})
#	message(STATUS "find pthread!--")
#endif()

add_executable(main ${MAIN_SRCS_LIST})
target_link_libraries(main luonetwork luothreadpool)
