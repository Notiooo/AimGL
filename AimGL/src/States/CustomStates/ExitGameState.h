#pragma once

#include "States/State.h"

class StateStack;

/**
 * @brief The state in which the player wants to close the game
 */
class ExitGameState : public State
{
public:
    explicit ExitGameState(StateStack& stack);
};