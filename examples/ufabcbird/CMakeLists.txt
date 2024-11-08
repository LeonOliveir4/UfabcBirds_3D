project("ufabcbird")
add_executable(${PROJECT_NAME} main.cpp window.cpp bird.cpp bg.cpp pipe.cpp)
enable_abcg(${PROJECT_NAME})