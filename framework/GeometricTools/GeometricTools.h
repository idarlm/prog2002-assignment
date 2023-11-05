#include <array>

namespace GeometricTools {
    constexpr std::array<float, 3*2> UnitTriangle2D = {
        -0.5f, -0.5f,   // bottom left
         0.5f, -0.5f,   // bottom right
         0.0f,  0.5f    // top center
    };

    constexpr std::array<float, 4*2> UnitSquare2D = {
        -0.5f, -0.5f,   // bottom left
         0.5f, -0.5f,   // bottom right
         0.5f,  0.5f,   // top right
        -0.5f,  0.5f    // top left
    };
}