find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})

add_library(inventory SHARED inventory.cpp)
add_library(item SHARED item.cpp)
add_library(userlist SHARED userlist.cpp)
add_library(utils SHARED utils.cpp)
add_library(vertex SHARED vertex.cpp)
add_library(polygon SHARED polygon.cpp)
add_library(map SHARED map.cpp)

add_library(display display.cpp)
add_library(shader shader.cpp)
add_library(mesh mesh.cpp)
add_library(texture texture.cpp)
add_library(transform transform.cpp)

# map depends on polygon and polygon depends on vertex
# only have to specify map, links to rest of the dependencies itself
target_link_libraries(map polygon)
target_link_libraries(polygon vertex)

target_link_libraries(userlist inventory)
target_link_libraries(inventory utils)
target_link_libraries(utils item)

target_link_libraries(shader transform)


add_executable(main main.cpp)


target_link_libraries(main display shader mesh texture map userlist 
                    ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} 
                    ${SDL2_LIBRARIES})
