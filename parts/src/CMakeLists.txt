add_library(item SHARED item.cpp)
add_library(inventory SHARED inventory.cpp)
add_library(userlist SHARED userlist.cpp)
add_library(utils SHARED utils.cpp)
add_library(vertex SHARED vertex.cpp)
add_library(polygon SHARED polygon.cpp)
add_library(map SHARED map.cpp)

add_executable(main main.cpp)

# map depends on polygon and polygon depends on vertex
# only have to specify map, links to rest of the dependencies itself
target_link_libraries(map polygon vertex)

target_link_libraries(main item inventory userlist utils map)