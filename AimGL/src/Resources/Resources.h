#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Resources/ResourceManager.h"


class Player;

/**
 * \brief Texture IDs under which individual textures can be saved and read.
 */
enum class TextureManagerId
{
    // Empty
};

/**
 * \brief Object storing textures of the game
 */
using TextureManager = ResourceManager<sf::Texture, TextureManagerId>;

// ====== Fonts ======= //

/**
 * \brief Fonts IDs under which individual font can be saved and read.
 */
enum class FontId
{
    ArialNarrow,
};

/**
 * \brief Object storing fonts of the game
 */
using FontManager = ResourceManager<sf::Font, FontId>;

/**
 * @brief Any game assets from textures or fonts
 */
struct GameResources
{
    TextureManager textureManager;
    FontManager fontManager;
};