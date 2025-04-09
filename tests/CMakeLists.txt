find_package(Qt6 REQUIRED COMPONENTS Test)

add_executable(test_task test_task.cpp)
target_link_libraries(test_task Qt5::Test)

add_test(NAME TestTask COMMAND test_task)
