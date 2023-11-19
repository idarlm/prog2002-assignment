#ifndef GEOMETRICTOOLS_H_
#define GEOMETRICTOOLS_H_

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
    const std::vector<float> UnitGridGeometry2D(unsigned columns, unsigned rows) {
        // vector to store the position values
        std::vector<float> pos = std::vector<float>();

        // calculate positions, working out way up one row at a time.
        for(int i = 0; i < rows+1; i++) {
            // calculate y position for this row
            float y = i * (1.f / (float)rows) - 0.5f;

            // calculate x positions for this row
            for (int i = 0; i < columns+1; i++) {
                float x = i * (1.f / (float)columns) - 0.5f;
                pos.push_back(x);
                pos.push_back(y);
            }
        }

        return pos;
    }

    /// @brief Calculates indices for UnitGridGeometry2D.
    /// @param columns - Number of horizontal divisions
    /// @param rows - Number of vertical divisions
    /// @return Array of indices
    const std::vector<unsigned> UnitGridTopologyTriangles(unsigned columns, unsigned rows) {
        /*
        Indices for any given row: (i drew this upside down for some reason)
        (n)___(n+1)__(n+2)__..
         |    . |    . |    . |
         | .    | .    | .    |
        (m)___(m+1)__(m+2)__..
        
        where n = row number * (columns + 1)
        and   m = (row number + 1) * (columns + 1)
        */

        // vector to store the indices
        std::vector<unsigned> indices = {};
        
        // work our way up starting from the bottom row
        for (int y = 0; y < rows; y++) {
            //calculate indices for each tile horizontally
            for (int x = 0; x < columns; x++) {
                // calculate indices
                auto n = x + y * (columns + 1);
                auto m = x + (y + 1) * (columns + 1);

                // triangle with corner in top left
                indices.push_back(m);
                indices.push_back(m+1);
                indices.push_back(n);

                // triangle with corner in bottom right
                indices.push_back(m+1);
                indices.push_back(n+1);
                indices.push_back(n);
            }
        }

        return indices;
    }
}

#endif