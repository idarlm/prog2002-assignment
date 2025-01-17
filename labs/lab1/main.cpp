#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <logger.h>
#include <GeometricTools.h>
#include "shaders.h"

GLuint makeTriangle();
GLuint makeSquare();
GLuint compileShader(const GLchar*, const GLchar*);

int main(int argc, char **argv)
{
    const char* tag = "Lab1";

    // GLFW error callback
    glfwSetErrorCallback( 
        [](int code, const char* msg)
        {
            Log::error("GLFWErrorCallback", (std::string)msg);
        }
    );

    // GLFW initialization
    if(!glfwInit())
    {
        Log::error(tag, "Failed to initialize GLFW.");
        return EXIT_FAILURE;
    }

    Log::info(tag, "GLFW Initialized.");

    // window creation
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    auto window = glfwCreateWindow(480, 360, "Test window", NULL, NULL);

    if(!window)
    {
        Log::error(tag, "Failed to create glfw window");
        return EXIT_FAILURE;
    }
    Log::info(tag, "Created Window");

    glfwMakeContextCurrent(window);

    // OpenGL initialization
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // OpenGL debugging settings
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(
        [] (GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* userParam)
        {
            std::cerr << "GL CALLBACK: "
                << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "")
                << " type = 0x" << type
                << ", severity = 0x" << severity
                << ", message = " << message << "\n";
        },
        0
    );
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

    // ..::DATA LOADING::..
    auto triangle = makeTriangle();
    auto triangleShaderProgram = compileShader(Shader::triVertexShaderSrc.c_str(), Shader::triFragmentShaderSrc.c_str());

    auto square = makeSquare();
    auto squareShaderProgram = compileShader(Shader::sqrVertexShaderSrc.c_str(), Shader::sqrFragmentShaderSrc.c_str());
    
    // ..::Application loop::..

    float time = 0;

    float timer = 1;
    int frameCount = 0;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        
        float newTime = glfwGetTime();
        float deltaTime = newTime - time;
        time = newTime;

        timer -= deltaTime;

        if(timer <= 0)
        {
            timer = 1;
            //Log::info(tag, "Frame count last second: " + std::to_string(frameCount));
            frameCount = 0;
        }

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // draw square
        glBindVertexArray(square);
        glUseProgram(squareShaderProgram);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        // draw triangle
        glBindVertexArray(triangle);
        glUseProgram(triangleShaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        frameCount++;
    }

    // ..::Termination::..
    // opengl cleanup
    glUseProgram(0);
    glDeleteProgram(triangleShaderProgram);
    glDeleteProgram(squareShaderProgram);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &triangle);
    glDeleteVertexArrays(1, &square);

    // glfw cleanup
    glfwDestroyWindow(window);
    Log::info(tag, "Destroyed window");

    glfwTerminate();
    Log::info(tag, "GLFW Terminated.");

    return EXIT_SUCCESS;
}

GLuint makeTriangle()
{
    // This function has overly detailed comments as i was taking notes 
    // from learnopengl and the khronos wiki.

    // array containing all the positions for the vertices in our triangle
    auto triangle = GeometricTools::UnitTriangle2D;

    // create vertex array object(VAO).
    // VAOs store the format of vertex data
    // as well as the buffer objects that store the data itself.
    // The buffer objects themselves will be made below.
    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId); // create a VAO and store its id
    glBindVertexArray(vertexArrayId);     // bind the VAO(tell opengl that we are working on this object).

    // create vertex buffer object(VBO).
    // VBO is the common name of a normal OpenGL buffer object when it is used to store vertex data.
    // vertex buffer objects store all the vertex data
    // we will need to draw the object/mesh.
    //
    // in this case we are only making one VBO that only holds vertex positions.
    GLuint vertexBufferId;
    glGenBuffers(1, &vertexBufferId);               // Create a buffer and store its id
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);  // Bind the buffer.
                                                    // This does not affect the VAO we have bound.
                                                    // The VAO will be affected later when we call glVertexAttribPointer

    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle.data(), GL_STATIC_DRAW);  // transfer the position data to the buffer we just bound.

    // Tell OpenGL what data we are providing in the currently bound buffer and how to read it.
    // This data is only now being added to the currently bound VAO.
    // This data will persist in the VAO regardless of what buffers we bind after this,
    // which is why the VAO is useful.
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, nullptr);
        // In this function call we are making an attribute with index 0 (which we reference in the vertex shader).
        // Then we are specifying that the attribute contains two floats.

    // Excerpt from the Khronos wiki about binding buffers and storing attributes in the VAO:
    /*

    Think of it like this. 
    glBindBuffer sets a global variable, then glVertexAttribPointer reads that global variable and stores it in the VAO. 
    Changing that global variable after it's been read doesn't affect the VAO. 
    You can think of it that way because that's exactly how it works. 

    */


    // Enable the vertex attribute array
    glEnableVertexAttribArray(0);

    return vertexArrayId;
}

GLuint makeSquare()
{
    auto square = GeometricTools::UnitSquare2D;

    GLubyte colors[4*3] = { // normalized unsigned bytes for colour data
        255, 255, 0,
          0, 255, 255,
        255,   0, 255,
        255, 255, 255
    };

    GLuint indices[3*2] = {
        0, 1, 2,
        0, 3, 2
    };

    // generate vertex array
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // generate buffers
    GLuint vbo[2];
    glGenBuffers(2, vbo);

    // vertex position buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square), square.data(), GL_STATIC_DRAW);

    // vertex color buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLubyte)*12, &colors, GL_DYNAMIC_DRAW);

    // index buffer
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // read buffer data into attrib array
    // position data:
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);

    // color data:
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, 3*sizeof(GLubyte), (void*)0);

    return vao;
}

GLuint compileShader(const GLchar* vss, const GLchar* fss)
{
    // compile vertex shader
    // vertex shaders define how a vertex is positioned,
    // as well as any other manipulation of vertex data.
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vss, nullptr);
    glCompileShader(vertexShader);

    // compile fragment shader
    // fragment shaders define the color of each fragment
    // (pixel) of the object we are drawing.
    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fss, nullptr);
    glCompileShader(fragmentShader);

    // create shader program
    auto shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // delete shaders from memory since they are now
    // stored in the shader program instead.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}