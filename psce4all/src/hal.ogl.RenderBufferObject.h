#ifndef hal_ogl_RenderBufferObject_h__
#define hal_ogl_RenderBufferObject_h__

#include "hal.ogl.Core.h"

namespace hal
{
    namespace ogl
    {
        class RenderBufferObject : protected Core
        {
        public:
            RenderBufferObject() : m_id(0)
            {
            }

            ~RenderBufferObject()
            {
                assert(("Render buffer object is not deleted", (m_id == 0)));
            }

            __forceinline void Create()
            {
                assert(("Render buffer object is already created", (m_id == 0)));

                __gl_DumpError glGenRenderbuffers(1, &m_id);
            }

            __forceinline void Delete()
            {
                assert(("Render buffer object is already deleted", (m_id != 0)));

                __gl_DumpError glDeleteRenderbuffers(1, &m_id);

                m_id = 0;
            }

            __forceinline void Bind()
            {
                __gl_DumpError glBindRenderbuffer(GL_RENDERBUFFER, m_id);
            }

            __forceinline void SetColorStorage(u32 width, u32 height)
            {
                __gl_DumpError glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA32F, (GLsizei)width, (GLsizei)height);
            }

            __forceinline void SetDepthStorage(u32 width, u32 height, GLenum internal_format = GL_DEPTH_COMPONENT16)
            {
                __gl_DumpError glRenderbufferStorage(GL_RENDERBUFFER, internal_format, (GLsizei)width, (GLsizei)height);
            }

            __forceinline void SetStencilStorage(u32 width, u32 height)
            {
                __gl_DumpError glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, (GLsizei)width, (GLsizei)height);
            }

            __forceinline void Unbind()
            {
                __gl_DumpError glBindRenderbuffer(GL_RENDERBUFFER, 0);
            }

            __forceinline GLuint Id() const
            {
                return m_id;
            }

        private:
            GLuint m_id;
        };
    }
}
#endif // hal_ogl_RenderBufferObject_h__
