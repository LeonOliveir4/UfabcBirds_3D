project("ufabcbird3d")
add_executable(${PROJECT_NAME} main.cpp window.cpp camera.cpp model.cpp bird.cpp modelObj.cpp ground.cpp animation.cpp fruta.cpp)
enable_abcg(${PROJECT_NAME})