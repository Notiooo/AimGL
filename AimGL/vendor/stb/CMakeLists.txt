message(STATUS "Fetching stb...")

FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb
        GIT_TAG beebb24b945efdea3b9bba23affb8eb3ba8982e7
)
FetchContent_MakeAvailable(stb)

message(STATUS "stb Fetched!")