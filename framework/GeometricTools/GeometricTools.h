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

    const std::vector<float> UnitCubePositions() {
        /* Cube face:
        *-------* z  
        |4     3| |_ x
        |       | 
        |1     2| Two such planes stacked vertically
        *-------*
        */
        std::vector<float> positions = {};

        for (int plane = 0; plane < 2; plane++) 
        {
            float y = -0.5f + (float)plane;

            // calculate positions for each point
            for (int pos = 0; pos < 4; pos++)
            {
                float x = -0.5f + (float)((pos + (pos/2)) % 2);
                float z = -0.5f + (float)(pos / 2);


                positions.push_back(x);
                positions.push_back(y);
                positions.push_back(z);
            }
        }

        return positions;
    }

    const std::vector<unsigned> UnitCubeIndices() {
        /*
        bottom/top:     |   sides:
        *-------*       |   *-------*
        |3/7 2/6|       |   |d     c|   where:  a = side
        |       |       |   |       |           b = (side + 1) % 4
        |0/4 1/5|       |   |a     b|           c = 4 + b
        *-------*       |   *-------*           d = 4 + side
                        |
        */
        std::vector<unsigned> indices = {};

        // bottom and top face
        for (int plane = 0; plane < 2; plane++)
        {
            unsigned offset = plane * 4;
        
            // upper left triangle (ref. drawing)
            indices.push_back(offset + 3);
            indices.push_back(offset + 2);
            indices.push_back(offset);
        
            // lower right triangle
            indices.push_back(offset + 2);
            indices.push_back(offset + 1);
            indices.push_back(offset);
        }

        //sides
        for (int side = 0; side < 4; side++)
        {
            unsigned a = side;
            unsigned b = (a + 1) % 4;
            unsigned c = 4 + b;
            unsigned d = 4 + a;
        
            // upper left triangle
            indices.push_back(d);
            indices.push_back(c);
            indices.push_back(a);
        
            // lower right triangle
            indices.push_back(c);
            indices.push_back(b);
            indices.push_back(a);
        }

        return indices;
    }

    // Constexpr version that generates the geometry of the grid, including texture coordinates
    // The shape of the generated data is PPTTPPTTPPTT..., meaning two components for position
    // and two components for texture coordinates.
    //
    // Implemented using same algorithm as old UnitGridGeometry2D()
    template<unsigned int X, unsigned int Y>
    constexpr std::array<float, (X + 1)* (Y + 1)* (2 + 2)> UnitGridGeometry2DWTCoords()
    {
        std::array<float, (X + 1)* (Y + 1)* (2 + 2)> array = {};
        int element = 0;

        // calculate positions, working out way up one row at a time.
        for (int i = 0; i < Y + 1; i++) {
            // calculate y position for this row
            float y = i * (1.f / (float)Y);

            // calculate x positions for this row
            for (int i = 0; i < X + 1; i++) {
                float x = i * (1.f / (float)X);
                // position data
                array[element++] = x - 0.5f;
                array[element++] = y - 0.5f;

                // texture coords
                array[element++] = x;
                array[element++] = y;
            }
        }

        return array;
    }

}

#endif