#include "StateStack.h"
#include "pch.h"

auto StateStack::createState(const State_ID& stateID)
{
    const auto found = mFactory.find(stateID);
    assert(found != mFactory.end());

    // As it find specific recipe in factory that
    // creates a state, then after it is found
    // we call that function to get a pointer to
    // this state, and we return it.
    return found->second();
}

void StateStack::applyChanges()
{
    for (const auto& change: mChangesQueue)
    {
        switch (change.operation)
        {
            case Perform::Push:
                spdlog::info("[StateStack] Pushing state: {}", toString(change.stateID));
                mStack.push_back({change.stateID, createState(change.stateID)});
                break;

            case Perform::Pop:
                spdlog::info("[StateStack] Poping state from the top ({})", toString(top()));
                mStack.pop_back();
                break;

            case Perform::Clear:
                spdlog::info("[StateStack] Clearing the StateStack");
                mStack.clear();
                break;
        }
    }
    mChangesQueue.clear();
}

void StateStack::fixedUpdate(const float& deltaTime)
{
    applyChanges();
    // Iterate from the highest state to the lowest state, and stop iterating if
    // any state returns
    for (auto beg = mStack.rbegin(), end = mStack.rend(); beg != end; ++beg)
    {
        // If a state is of "Transparent" type, then we iterate further
        // But if it returns false, then we stop iterating.

        // This allow some states to pause states under it.
        // Like pause for example
        if (!(*beg).state->fixedUpdate(deltaTime))
        {
            return;
        }
    }
}

void StateStack::update(const float& deltaTime)
{
    applyChanges();
    // Iterate from the highest state to the lowest state, and stop iterating if
    // any state returns
    for (auto beg = mStack.rbegin(), end = mStack.rend(); beg != end; ++beg)
    {
        // If a state is of "Transparent" type, then we iterate further
        // But if it returns false, then we stop iterating.

        // This allow some states to pause states under it.
        // Like pause for example
        if (!(*beg).state->update(deltaTime))
        {
            return;
        }
    }
}

void StateStack::updateImGui(const float& deltaTime)
{
    applyChanges();
    // Iterate from the highest state to the lowest state, and stop iterating if
    // any state returns
    for (auto beg = mStack.rbegin(), end = mStack.rend(); beg != end; ++beg)
    {
        // If a state is of "Transparent" type, then we iterate further
        // But if it returns false, then we stop iterating.

        // This allow some states to pause states under it.
        // Like pause for example
        if (!(*beg).state->updateImGui(deltaTime))
        {
            return;
        }
    }
}

void StateStack::draw(sf::Window& target) const
{
    // Drawing starts from the lowest state to the highest state
    for (const auto& entry: mStack)
    {
        entry.state->draw(target);
    }
}

void StateStack::handleEvent(const sf::Event& event)
{
    applyChanges();

    // Iterate from the highest state to the lowest state, and stop iterating if
    // any state returns
    for (auto beg = mStack.rbegin(), end = mStack.rend(); beg != end; ++beg)
    {
        // If a state is of "Transparent" type, then we iterate further
        // But if it returns false, then we stop iterating.

        // This allow some states to pause states under it.
        // Like pause for example
        if (!(*beg).state->handleEvent(event))
        {
            return;
        }
    }
}


void StateStack::push(State_ID stateID)
{
    mChangesQueue.emplace_back(Change{Perform::Push, stateID});
}

void StateStack::pop()
{
    mChangesQueue.emplace_back(Change{Perform::Pop, State_ID::None});
}

void StateStack::clear()
{
    mChangesQueue.emplace_back(Change{Perform::Clear, State_ID::None});
}

bool StateStack::empty() const noexcept
{
    return mStack.empty();
}

State_ID StateStack::top() const
{
    if (empty())
    {
        return State_ID::None;
    }
    return mStack.back().id;
}

void StateStack::forceInstantClear()
{
    spdlog::warn("[StateStack] Statestack is forced to clear all its states instantly");
    mStack.clear();
}
