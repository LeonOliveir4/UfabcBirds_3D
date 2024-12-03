project("ufabcbird3d")
add_executable(${PROJECT_NAME} main.cpp window.cpp modelObj.cpp camera.cpp model.cpp model_2.cpp ground.cpp)
enable_abcg(${PROJECT_NAME})