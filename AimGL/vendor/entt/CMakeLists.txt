message(STATUS "Fetching Entt...")

FetchContent_Declare(
        entt
        GIT_REPOSITORY https://github.com/skypjack/entt
        GIT_TAG 717897052477515260bde3fd21fe987662666621
)
FetchContent_MakeAvailable(entt)

message(STATUS "Entt Fetched!")