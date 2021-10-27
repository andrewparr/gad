add_library(doomsday doomsday.cpp)
target_include_directories(doomsday PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(doomsday date)

add_executable(gad main.cpp)
target_link_libraries(gad doomsday ${Boost_PROGRAM_OPTIONS_LIBRARY})