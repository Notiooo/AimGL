include(FetchContent)

include(sfml/CMakeLists.txt)
include(imgui/CMakeLists.txt)
include(imgui-sfml/CMakeLists.txt)

add_subdirectory(glm)
add_subdirectory(glew)
add_subdirectory(spdlog)
add_subdirectory(result)
add_subdirectory(entt)
add_subdirectory(minitrace)