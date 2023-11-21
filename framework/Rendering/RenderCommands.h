#ifndef RENDERINGCOMMANDS_H

#include <glad/glad.h>
#include <memory>
#include "VertexArray.h"

namespace RenderCommands
{
    inline void Clear(GLuint mode = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    {
        glClear(mode);
    }

    inline void SetPolygonMode(GLenum face, GLenum mode)
    {
        glPolygonMode(face, mode);
    }

    inline void DrawIndex(const std::shared_ptr<VertexArray>& vao, GLenum primitive = GL_TRIANGLES)
    {
        glDrawElements(primitive, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    inline void SetClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) 
    {
        glClearColor(r, g, b, a);
    }

    inline void SetWireframeMode()
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    inline void SetSolidMode()
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    inline void EnableDepthTest()
    {
        glEnable(GL_DEPTH_TEST);
    }

    inline void DisableDepthTest()
    {
        glDisable(GL_DEPTH_TEST);
    }
}


#endif // !RENDERINGCOMMANDS_H
