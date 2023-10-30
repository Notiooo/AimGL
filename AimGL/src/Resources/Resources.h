#pragma once

#include "Resources/ResourceManager.h"
#include <Renderer3D/Font.h>
#include <Renderer3D/Texture.h>


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
using TextureManager = ResourceManager<Texture, TextureManagerId>;

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
using FontManager = ResourceManager<Font, FontId>;

/**
 * @brief Any game assets from textures or fonts
 */
struct GameResources
{
    TextureManager textureManager;
    FontManager fontManager;
};