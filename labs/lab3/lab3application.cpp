#include <logger.h>
#include <glad/glad.h>
#include <GeometricTools.h>
#include <ShaderDataTypes.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <RenderCommands.h>
#include <stb_image.h>
#include "lab3application.h"
#include "shaders.h"

Lab3Application::Lab3Application(std::string name, std::string version) 
    : GLFWApplication(name, version) {}

unsigned Lab3Application::Init() 
{
    if (GLFWApplication::Init() != GLFWApplication::OK) 
    {
        Log::error("Lab3Application", "Failed to init GLFWApplication.");
        return 1;
    }

    // create VAO
    m_vertArray = std::make_shared<VertexArray>();

    // create VBO
    auto verts = GeometricTools::UnitGridGeometry2DWTCoords<8, 8>();
    auto vbuff = std::make_shared<VertexBuffer>(verts.data(), verts.size() * sizeof(float));
    vbuff->SetLayout(
        BufferLayout({
            {ShaderDataType::Float2, "position"},
            {ShaderDataType::Float2, "tex_coords"}
        })
    );

    // create EBO
    auto indices = GeometricTools::UnitGridTopologyTriangles(8, 8);   
    auto ibuff = std::make_shared<IndexBuffer>(indices.data(), indices.size());

    m_vertArray->AddVertexBuffer(vbuff);
    m_vertArray->SetIndexBuffer(ibuff);

    // create shader program
    m_shaderProg = std::make_shared<Shader>(
        Lab3Shaders::sqrVertexShaderSrc,
        Lab3Shaders::sqrFragmentShaderSrc
    );

    // create cube
    m_cube = std::make_shared<VertexArray>();
    auto v = GeometricTools::UnitCubePositions();
    auto i = GeometricTools::UnitCubeIndices();

    auto vb = std::make_shared<VertexBuffer>(v.data(), v.size() * sizeof(float));
    vb->SetLayout(BufferLayout({ {ShaderDataType::Float3, "position"} }));
    auto ib = std::make_shared<IndexBuffer>(i.data(), i.size());

    m_cube->AddVertexBuffer(vb);
    m_cube->SetIndexBuffer(ib);

    m_cubeShader = std::make_shared<Shader>(Lab3Shaders::cubeVertShader, Lab3Shaders::cubeFragShader);

    // load image
    auto filepath = std::string(TEXTURES_DIR) + std::string("floor_texture.png");
    int width, height, bpp;
    auto pixels = stbi_load(filepath.c_str(), &width, &height, &bpp, STBI_rgb_alpha);
    if (!pixels)
    {
        Log::error("Lab3", "Failed to load texture: ", filepath);
        return 1;
    }
    Log::info("Lab3", "Image loaded successfully! (", width, "x", height, "px)");

    GLuint tex;
    glGenTextures(1, &tex);

    GLuint slot = 0;
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    //Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(pixels);

    return 0;
}

unsigned Lab3Application::Run() const 
{
    Log::info("Lab3Application", "Starting application loop");
    GLint selected = 0;
    auto u_selected = m_shaderProg->GetUniformLocation("selected_vertex");

    auto projectionMatrix = glm::perspective(45.f, 1280.f / 720.f, 0.1f, 10.f);
    auto viewMatrix = glm::lookAt(glm::vec3(0.f, 2.f, 2.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    auto modelMatrix = glm::mat4(1.f);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(2.f, 2.f, 2.f));

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) 
    {
        glfwPollEvents();

        // clear window
        RenderCommands::SetClearColor(0.1f, 0.25f, 0.5f, 1.0f);
        RenderCommands::Clear();

        // draw board
        m_vertArray->Bind();
        m_shaderProg->Bind();

        // update selected tile
        selected = (9 * (selectionY % 8)) + (selectionX % 8);
        glUniform1i(u_selected, selected);

        m_shaderProg->UploadUniformMat4x4("projection", projectionMatrix);
        m_shaderProg->UploadUniformMat4x4("view", viewMatrix);
        m_shaderProg->UploadUniformMat4x4("model", modelMatrix);
        RenderCommands::DrawIndex(m_vertArray);

        // draw cube
        auto time = (float)glfwGetTime();
        auto cubeModel = glm::mat4(1.f);
        cubeModel = glm::translate(cubeModel, glm::vec3(0.f, 0.5f, 0.f));
        cubeModel = glm::rotate(cubeModel, -time, glm::vec3(0.f, 1.f, 0.f));
        m_cube->Bind();
        m_cubeShader->Bind();
        m_cubeShader->UploadUniformMat4x4("projection", projectionMatrix);
        m_cubeShader->UploadUniformMat4x4("view", viewMatrix);
        m_cubeShader->UploadUniformMat4x4("model", cubeModel);
        auto loc = m_cubeShader->GetUniformLocation("alt_color");

        RenderCommands::DrawIndex(m_cube);
        RenderCommands::SetWireframeMode();
        glUniform1i(loc, 1);
        RenderCommands::DrawIndex(m_cube);
        RenderCommands::SetSolidMode();
        glUniform1i(loc, 0);


        // display new frame
        glfwSwapBuffers(window);
    }

    return 0;
}