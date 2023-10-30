message(STATUS "Fetching ImGui...")

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG c6e0284ac58b3f205c95365478888f7b53b077e2 # release v1.89.9
)
FetchContent_MakeAvailable(imgui)

message(STATUS "ImGui Fetched!")