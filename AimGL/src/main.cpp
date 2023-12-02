#include "Game.h"
#include "constants.h"
#include "pch.h"

int main()
{
#if (defined(_MSC_VER) && defined(_DEBUG))
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

#if defined(_DEBUG)
    spdlog::set_level(spdlog::level::debug);
    #ifdef MTR_ENABLED
    spdlog::warn("MiniTrace is enabled!");
    #endif
#endif

    try
    {
        auto game = std::make_unique<Game>();
        game->run();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }

    return 0;
}
