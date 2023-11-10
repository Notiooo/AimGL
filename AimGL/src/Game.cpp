#include "Game.h"
#include "States/CustomStates/ExitGameState.h"
#include "States/CustomStates/LogoState.h"
#include "constants.h"
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
#ifndef _DEBUG
    settings.attributeFlags = sf::ContextSettings::Core;
#endif

    // settings.attributeFlags = sf::ContextSettings::Core;

    // If Core should be used, then there is
    // a need to change the way ImGui is plugged in. For the moment ImGui-SFML uses the SFML
    // graphics module - so ImGui will not draw on Core setting. This project is developed without
    // the SFML graphics module and works without it. In the future, it would be useful to plug in
    // ImGui in such a way that it no longer relies on the SFML graphics module.

    mGameWindow =
        std::make_unique<WindowToRender>(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "AimGL",
                                         sf::Style::Titlebar | sf::Style::Close, settings);

    mGameWindow->setFramerateLimit(FRAMES_PER_SECOND);
    mGameWindow->setActive(true);
    loadResources();

#ifdef _DEBUG
    ImGui::SFML::Init(*mGameWindow, sf::Vector2f(mGameWindow->getSize()), true);
#endif

    // GLEW setup
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Setup all application-flow states
    mAppStack.saveState<LogoState>(State_ID::LogoState, *mGameWindow);
    mAppStack.saveState<ExitGameState>(State_ID::ExitGameState);

    // Initial state of the statestack is TitleState
    mAppStack.push(State_ID::LogoState);
}

void Game::run()
{
    spdlog::info("Game starts, the resolution is {}x{}", mGameWindow->getSize().x,
                 mGameWindow->getSize().y);

    mtr_init("chrome-trace.json");
    if constexpr (not IS_MINITRACE_COLLECTING_AT_START)
    {
        mtr_stop();
    }
    else
    {
        spdlog::info("Minitrace started collecting data");
    }
    MTR_META_PROCESS_NAME("Game");
    MTR_META_THREAD_NAME("main thread");

    performGameLoop();

    mGameWindow->close();
#ifdef _DEBUG
    ImGui::SFML::Shutdown();
#endif
    mtr_flush();
    mtr_shutdown();
}

void Game::performGameLoop()
{
    MTR_SCOPE("Game", "Game::performGameLoop");
    sf::Clock clock;
    auto frameTimeElapsed = sf::Time::Zero;
    mFixedUpdateClock.restart();
    while (isGameRunning)
    {
        MTR_SCOPE("Game", "GameLoop");
        frameTimeElapsed = clock.restart();
        update(frameTimeElapsed);
        fixedUpdateAtEqualIntervals();
        processEvents();

        render();

        mtr_flush();
    }
    mAppStack.forceInstantClear();
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

void Game::updateImGuiMiniTrace()
{
#ifdef MTR_ENABLED
    static bool isMinitraceCollecting = IS_MINITRACE_COLLECTING_AT_START;
    ImGui::Begin("MiniTrace", 0, ImGuiWindowFlags_AlwaysAutoResize);
    if (isMinitraceCollecting)
    {
        ImGui::Text("Collecting minitrace...");
    }
    else
    {
        ImGui::Text("Idle...");
    }
    if (ImGui::Button("Start collecting trace"))
    {
        mtr_start();
        isMinitraceCollecting = true;
        spdlog::info("Minitrace started collecting data");
    }
    ImGui::SameLine();
    if (ImGui::Button("Stop collecting trace"))
    {
        mtr_stop();
        isMinitraceCollecting = false;
        spdlog::info("Minitrace stopped collecting data");
    }
    ImGui::End();
#endif
}

void Game::updateImGui(sf::Time deltaTime)
{
#ifdef _DEBUG

    ImGui::SFML::Update(sf::Mouse::getPosition(*mGameWindow), sf::Vector2f(mGameWindow->getSize()),
                        deltaTime);

    updateImGuiMiniTrace();
    mAppStack.updateImGui(deltaTime.asSeconds());
#endif
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

    updateImGui(deltaTime);

    mAppStack.update(deltaTimeInSeconds);

    if (mAppStack.top() == State_ID::ExitGameState)
    {
        isGameRunning = false;
    }
}

void Game::render()
{
    MTR_SCOPE("Game", "Game::render");
    glClearColor(0.f, 0.f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw the application
    mAppStack.draw(*mGameWindow);

#ifdef _DEBUG
    mGameWindow->pushGLStates();
    ImGui::SFML::Render();
    mGameWindow->popGLStates();
#endif

    // display to the window
    mGameWindow->display();
}


void Game::loadResources()
{
    // Empty
}