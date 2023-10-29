message(STATUS "Fetching MiniTrace...")

FetchContent_Declare(
        minitrace
        GIT_REPOSITORY https://github.com/hrydgard/minitrace
        GIT_TAG bc377c921f8c7da38f2beab355245222a01efc1a
)
FetchContent_MakeAvailable(minitrace)

message(STATUS "MiniTrace Fetched!")