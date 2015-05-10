#ifndef hal_ogl_VertexArrayObject_h__
#define hal_ogl_VertexArrayObject_h__

#include "hal.ogl.DeletableObject.h"

namespace hal
{
    namespace ogl
    {
        class VertexArrayObject : protected DeletableObject
        {
        public:
            VertexArrayObject(GLuint id = 0) : DeletableObject(id)
            {
            }

            ~VertexArrayObject()
            {
            }

            void Create()
            {
                __gl_DebugInfo AssertCreate([](DeletableObject * that){ __gl_DumpError glGenVertexArrays(1, &(that->m_id)); });
            }

            void Delete()
            {
                __gl_DebugInfo AssertDelete([](DeletableObject * that){ __gl_DumpError glDeleteVertexArrays(1, &(that->m_id)); });
            }

            void Bind()
            {
                __gl_DumpError glBindVertexArray(m_id);
            }

            void BufferBase()
            {
            }

            void Unbind()
            {
                __gl_DumpError glBindVertexArray(0);
            }

            using DeletableObject::Id;
            using DeletableObject::Deletable;
        };
    }
}

#endif // hal_ogl_VertexArrayObject_h__
