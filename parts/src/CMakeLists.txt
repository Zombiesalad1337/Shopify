add_library(item SHARED item.cpp)
add_library(inventory SHARED inventory.cpp)
add_library(userlist SHARED userlist.cpp)
add_library(utils SHARED utils.cpp)

add_executable(main main.cpp)

target_link_libraries(main item inventory userlist utils)