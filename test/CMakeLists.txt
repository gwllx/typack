project(test LANGUAGES CXX)

add_executable(typack_test typack_test.cpp)
target_link_libraries(typack_test PRIVATE typack)

add_test(NAME typack_test COMMAND typack_test)
