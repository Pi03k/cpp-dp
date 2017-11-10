file(GLOB_RECURSE TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)

set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_tests)

add_executable (${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
target_link_libraries(${PROJECT_TEST_NAME} ${PROJECT_LIB_NAME})

if(Boost_FOUND)
    target_link_libraries(${PROJECT_TEST_NAME} ${Boost_LIBRARIES})
endif()

enable_testing(true)

add_test(tests ${PROJECT_TEST_NAME})