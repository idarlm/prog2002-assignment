#include <logger.h>
#include <glad/glad.h>
#include <GeometricTools.h>
#include <ShaderDataTypes.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
        Lab3Shaders::sqrVertexShaderSrc, 
        Lab3Shaders::sqrFragmentShaderSrc
    );

    return 0;
}

unsigned Lab3Application::Run() const 
{
    Log::info("Lab3Application", "Starting application loop");
    GLint selected = 0;
    auto u_selected = m_shaderProg->GetUniformLocation("selected_vertex");

    auto projectionMatrix = glm::perspective(45.f, 480.f / 360.f, 0.1f, 10.f);
    auto viewMatrix = glm::lookAt(glm::vec3(0.f, 2.f, 2.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    auto modelMatrix = glm::mat4(1.f);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(2.f, 2.f, 2.f));

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) 
    {
        glfwPollEvents();

        auto time = (float)glfwGetTime();
        auto modelMatrix2 = glm::mat4(1.f);
        modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(0.f, 2.f * sin(time), 0.f));
        modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(0.f, -2.5f, 0.f));
        modelMatrix2 = glm::rotate(modelMatrix2, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
        modelMatrix2 = glm::rotate(modelMatrix2, time, glm::vec3(0.f, 0.f, 1.f));
        modelMatrix2 = glm::scale(modelMatrix2, glm::vec3(2.f, 2.f, 2.f));

        // update selected tile
        selected = (9 * (selectionY % 8)) + (selectionX % 8);
        glUniform1i(u_selected, selected);

        // clear window
        glClearColor(0.1f, 0.25f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw board
        m_vertArray->Bind();
        m_shaderProg->Bind();
        m_shaderProg->UploadUniformMat4x4("projection", projectionMatrix);
        m_shaderProg->UploadUniformMat4x4("view", viewMatrix);
        m_shaderProg->UploadUniformMat4x4("model", modelMatrix);
        glDrawElements(GL_TRIANGLES, m_vertArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

        m_shaderProg->UploadUniformMat4x4("model", modelMatrix2);
        glDrawElements(GL_TRIANGLES, m_vertArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

        // display new frame
        glfwSwapBuffers(window);
    }

    return 0;
}