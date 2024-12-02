project("ufabcbird3d")
add_executable(${PROJECT_NAME} main.cpp window.cpp modelObj.cpp camera.cpp ground.cpp)
enable_abcg(${PROJECT_NAME})