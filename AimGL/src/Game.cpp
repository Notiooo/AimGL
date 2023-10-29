#include "Game.h"
#include "pch.h"


constexpr int FRAMES_PER_SECOND = 120;

/**
 * @brief I kindly ask that the following variable not be changed, as the
 * physics calculations have been adjusted under the following framerate.
 * Thank you.
 *
 * @warning If you do not comply, the player will move differently and jump lower or higher.
 */
constexpr int MINIMAL_FIXED_UPDATES_PER_FRAME = 120;

const sf::Time Game::TIME_PER_FIXED_UPDATE_CALLS =
    sf::seconds(1.f / MINIMAL_FIXED_UPDATES_PER_FRAME);
const int Game::SCREEN_WIDTH = 1280;
const int Game::SCREEN_HEIGHT = 720;

Game::Game()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    settings.depthBits = 24;
    settings.stencilBits = 8;

    mGameWindow =
        std::make_unique<sf::RenderWindow>(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "AimGL",
                                           sf::Style::Titlebar | sf::Style::Close, settings);

    mGameWindow->setFramerateLimit(FRAMES_PER_SECOND);
    mGameWindow->setActive(true);
    loadResources();

#ifdef _DEBUG
    ImGui::SFML::Init(*mGameWindow);
#endif

    // GLEW setup
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    // Setup all application-flow states
    // mAppStack.saveState<...>(State_ID::GameState, *mGameWindow, mGameResources);

    // Initial state of the statestack is TitleState
    // mAppStack.push(State_ID::...);
}

void Game::run()
{
    spdlog::info("Game starts, the resolution is {}x{}", mGameWindow->getSize().x,
                 mGameWindow->getSize().y);

    mtr_init("chrome-trace.json");
    MTR_META_PROCESS_NAME("Game");
    MTR_META_THREAD_NAME("main thread");

    performGameLoop();

    mGameWindow->close();
    ImGui::SFML::Shutdown();
    mtr_flush();
    mtr_shutdown();
}

void Game::performGameLoop()
{
    sf::Clock clock;
    auto frameTimeElapsed = sf::Time::Zero;
    mFixedUpdateClock.restart();
    while (isGameRunning)
    {
        MTR_SCOPE("Game", "GameLoop");
        frameTimeElapsed = clock.restart();
#ifdef _DEBUG
        ImGui::SFML::Update(*mGameWindow, frameTimeElapsed);
#endif
        update(frameTimeElapsed);
        fixedUpdateAtEqualIntervals();
        processEvents();

        render();

        mtr_flush();
    }
}

void Game::fixedUpdateAtEqualIntervals()
{
    MTR_SCOPE("Game", "Game::fixedUpdateAtEqualIntervals");
    mTimeSinceLastFixedUpdate += mFixedUpdateClock.restart();
    if (mTimeSinceLastFixedUpdate > TIME_PER_FIXED_UPDATE_CALLS)
    {
        do
        {
            mTimeSinceLastFixedUpdate -= TIME_PER_FIXED_UPDATE_CALLS;
            fixedUpdate(TIME_PER_FIXED_UPDATE_CALLS);
        }
        while (mTimeSinceLastFixedUpdate > TIME_PER_FIXED_UPDATE_CALLS);
    }
}

void Game::processEvents()
{
    MTR_SCOPE("Game", "Game::processEvents");
    sf::Event event;
    while (mGameWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            isGameRunning = false;
        }

#ifdef _DEBUG
        ImGui::SFML::ProcessEvent(event);
#endif

        mAppStack.handleEvent(event);
    }
}

void Game::fixedUpdate(const sf::Time& deltaTime)
{
    MTR_SCOPE("Game", "Game::fixedUpdate");
    auto deltaTimeInSeconds = deltaTime.asSeconds();
    mAppStack.fixedUpdate(deltaTimeInSeconds);
}

void Game::update(const sf::Time& deltaTime)
{
    MTR_SCOPE("Game", "Game::update");
    auto deltaTimeInSeconds = deltaTime.asSeconds();

    mAppStack.update(deltaTimeInSeconds);

    if (mAppStack.top() == State_ID::ExitGameState)
    {
        isGameRunning = false;
    }
}

void Game::render()
{
    MTR_SCOPE("Game", "Game::render");
    glClearColor(0.43f, 0.69f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw the application
    mAppStack.draw(*mGameWindow, sf::Transform::Identity);

#ifdef _DEBUG
    mGameWindow->pushGLStates();
    ImGui::SFML::Render(*mGameWindow);
    mGameWindow->popGLStates();
#endif

    // display to the window
    mGameWindow->display();
}


void Game::loadResources()
{
    // Empty
}