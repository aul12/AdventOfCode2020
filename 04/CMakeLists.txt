project(04)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} stdc++fs)
