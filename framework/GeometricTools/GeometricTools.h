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
        // vector to store the position values
        std::vector<float> pos{};

        // calculate positions, working out way down one row at a time.
        for(int i = 0; i < rows+1; i++) {
            // calculate y position for this row
            float y = i * (1.f / (float)columns);

            // calculate x positions for this row
            for (int i = 0; i < columns+1; i++) {
                float x = i * (1.f / (float)rows);
                pos.push_back(x);
                pos.push_back(y);
            }
        }

        return pos.data();
    }

    /// @brief Calculates indices for UnitGridGeometry2D.
    /// @param columns Number of horizontal divisions
    /// @param rows Number of vertical divisions
    /// @return Array of indices
    const float *UnitGridTopologyTriangles(unsigned columns, unsigned rows) {
        /*
        Indices:
        (n)___(n+1)__(n+2)__..
         |    . |    . |    . |
         | .    | .    | .    |
        (m)___(m+1)__(m+2)__..
        
        where n = row number * columns.
        and   m = (row number + 1) * columns
        */

        // vector to store the indices
        std::vector<int> indices{};
        
        // work our way down starting from the top row
        for (int y = 0; y < rows; y++) {
            //calculate indices for each tile horizontally
            for (int x = 0; x < columns; x++) {
                // calculate indices
                auto n = y * columns;
                auto m = (y + 1) * columns;

                // triangle with corner in top left
                indices.push_back(n);
                indices.push_back(n+1);
                indices.push_back(m);

                // triangle with corner in bottom right
                indices.push_back(m+1);
                indices.push_back(m);
                indices.push_back(n+1);
            }
        }
    }
}