add_executable(main main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

add_library(display display.cpp)
add_library(shader shader.cpp)
add_library(mesh mesh.cpp)
add_library(texture texture.cpp)
add_library(transform transform.cpp)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})

target_link_libraries(shader transform)

target_link_libraries(main display shader mesh texture 
                    ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} 
                    ${SDL2_LIBRARIES})
