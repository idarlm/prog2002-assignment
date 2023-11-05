#include <array>
#include <vector>

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

    /// @brief Makes a unit sized grid of positions.
    /// @param columns Number of horizontal divisions
    /// @param rows Number of vertival divisions
    /// @return Array of values.
    const float *UnitGridGeometry2D(unsigned columns, unsigned rows) {
        // vector to store the values
        std::vector<float> arr{};

        // calculate positions, working out way down one row at a time.
        for(int i = 0; i < rows+1; i++) {
            // calculate y position for this row
            float y = i * (1.f / (float)columns);

            // calculate x positions for this row
            for (int i = 0; i < columns+1; i++) {
                float x = i * (1.f / (float)rows);
                arr.push_back(x);
                arr.push_back(y);
            }
        }

        return arr.data();
    }
}