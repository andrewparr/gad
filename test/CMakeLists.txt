set(TEST_SOURCES
    test_gad.cpp
)

add_executable(test_gad ${TEST_SOURCES})
target_link_libraries(test_gad doomsday)

add_test(test_gad ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_gad)
