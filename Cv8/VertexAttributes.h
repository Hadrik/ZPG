//
// Created by trric on 2026-11-08.
//

#ifndef ZPG_VERTEXATTRIBUTE_H
#define ZPG_VERTEXATTRIBUTE_H
#include <bit>


namespace VertexAttributes {
    enum class Attributes : unsigned {
        None = 0,
        Color = 1 << 0,
        Uv = 1 << 2
    };

    constexpr Attributes operator|(Attributes a, Attributes b) {
        return static_cast<Attributes>(static_cast<unsigned>(a) | static_cast<unsigned>(b));
    }

    constexpr bool hasAttribute(Attributes attr, Attributes check) {
        return (static_cast<unsigned>(attr) & static_cast<unsigned>(check)) != 0;
    }

    constexpr int count(Attributes attr) {
        return std::popcount(static_cast<unsigned>(attr));
    }
}



#endif //ZPG_VERTEXATTRIBUTE_H
