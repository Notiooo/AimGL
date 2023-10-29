message(STATUS "Fetching Result...")

FetchContent_Declare(
        result
        GIT_REPOSITORY https://github.com/bitwizeshift/result
        GIT_TAG a97e66bc66f140132619fd5f5cdffc30127f4220
)
FetchContent_MakeAvailable(result)

message(STATUS "Result Fetched!")