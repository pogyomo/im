add_executable(forward_list_test main.cc)
target_link_libraries(forward_list_test
    PRIVATE ${PROJECT_NAME}
)

add_test(NAME run_forward_list_test COMMAND forward_list_test)
