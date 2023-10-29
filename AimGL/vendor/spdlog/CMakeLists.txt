message(STATUS "Fetching Spdlog...")

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG 3aceda041b2bfbccaf14d5c83eda16fc67bea364
)
FetchContent_MakeAvailable(spdlog)

message(STATUS "Spdlog Fetched!")