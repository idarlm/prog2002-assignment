#include <logger.h>
#include <glad/glad.h>
#include <GeometricTools.h>
#include <ShaderDataTypes.h>
#include "lab2application.h"
#include "shaders.h"

Lab2Application::Lab2Application(std::string name, std::string version) 
    : GLFWApplication(name, version) {}

unsigned Lab2Application::Init() 
{
    if (GLFWApplication::Init() != GLFWApplication::OK) 
    {
        Log::error("Lab2Application", "Failed to init GLFWApplication.");
        return 1;
    }

    // create VAO
    m_vertArray = std::make_shared<VertexArray>();

    // create VBO
    auto verts = GeometricTools::UnitGridGeometry2D(8, 8);
    auto vbuff = std::make_shared<VertexBuffer>(verts.data(), verts.size() * sizeof(float));
    vbuff->SetLayout(
        BufferLayout({
            {ShaderDataType::Float2, "position"}
        })
    );

    // create EBO
    auto indices = GeometricTools::UnitGridTopologyTriangles(8, 8);   
    auto ibuff = std::make_shared<IndexBuffer>(indices.data(), indices.size());

    m_vertArray->AddVertexBuffer(vbuff);
    m_vertArray->SetIndexBuffer(ibuff);

    // create shader program
    m_shaderProg = std::make_shared<Shader>(
        Lab2Shaders::sqrVertexShaderSrc, 
        Lab2Shaders::sqrFragmentShaderSrc
    );

    return 0;
}

unsigned Lab2Application::Run() const 
{
    Log::info("Lab2Application", "Starting application loop");
    GLint selected = 0;
    auto u_selected = m_shaderProg->GetUniformLocation("selected_vertex");

    while (!glfwWindowShouldClose(window)) 
    {
        glfwPollEvents();
        
        // update selected tile
        selected = (9 * (selectionY % 8)) + (selectionX % 8);
        glUniform1i(u_selected, selected);

        // clear window
        glClearColor(0.1f, 0.25f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw board
        m_vertArray->Bind();
        m_shaderProg->Bind();
        glDrawElements(GL_TRIANGLES, m_vertArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

        // display new frame
        glfwSwapBuffers(window);
    }

    return 0;
}