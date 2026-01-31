#pragma once

#include <nn/math/Vector.hpp>

using Vector2u8 = nn::math::Vector2u8;
using Vector2i = nn::math::Vector2i;

inline constexpr u32 unitBaseNum = 16;
inline constexpr u32 maxLayerNum = 2;

inline constexpr u32 townBlockXNum = 7;
inline constexpr u32 townBlockZNum = 6;
inline constexpr u32 townFgBlockXNum = townBlockXNum - 2;
inline constexpr u32 townFgBlockZNum = townBlockZNum - 2;
inline constexpr u32 townFgBlockTotalNum = townFgBlockXNum * townFgBlockZNum;

inline constexpr u32 islandBlockXNum = 4;
inline constexpr u32 islandBlockZNum = 4;
inline constexpr u32 islandFgBlockXNum = islandBlockXNum - 2;
inline constexpr u32 islandFgBlockZNum = islandBlockZNum - 2;
