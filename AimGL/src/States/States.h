#ifndef STATES_H
#define STATES_H

/**
 * \brief Identifiers of individual states that can be used.
 */
enum class State_ID
{
    // === Application flow states === //
    None,
    LogoState,
    GameState,
    PauseState,

    ExitGameState
};

/**
 * \brief Converts state identifier to text
 * \param stateId State identifier
 * \return Textual representation of the state
 */
inline std::string toString(State_ID stateId)
{
    switch (stateId)
    {

        case State_ID::None: return "None";
        case State_ID::LogoState: return "LogoState";
        case State_ID::GameState: return "GameState";
        case State_ID::PauseState: return "PauseState";
        case State_ID::ExitGameState: return "ExitGameState";
        default:
            spdlog::warn("I was unable to perform the ID to text conversion.");
            return "Unknown State_ID";
    }
}


#endif