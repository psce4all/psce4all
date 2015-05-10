#ifndef gl_vbo_h__
#define gl_vbo_h__

#include "hal.ogl.BufferObject.h"

namespace hal
{
    namespace ogl
    {
        class VertexBufferObject : public BufferObject< GL_ARRAY_BUFFER >
        {
        public:
            VertexBufferObject()
            {
            }

            ~VertexBufferObject()
            {
            }

            using BufferObject< GL_ARRAY_BUFFER >::Create;
            using BufferObject< GL_ARRAY_BUFFER >::Delete;
            using BufferObject< GL_ARRAY_BUFFER >::Bind;
            using BufferObject< GL_ARRAY_BUFFER >::Unbind;
            using BufferObject< GL_ARRAY_BUFFER >::Map;
            using BufferObject< GL_ARRAY_BUFFER >::Unmap;

            __forceinline void Bind(u32 size)
            {
                __gl_DebugInfo Bind(0, size);
            }

            __forceinline void Bind(void const *data, u32 size)
            {
                __gl_DebugInfo Bind();
                __gl_DumpError glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
            }

            __forceinline void Bind(void const *data, u32 offset, u32 size)
            {
                __gl_DebugInfo Bind();
                __gl_DumpError glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
            }

            __forceinline void SetData(u32 size)
            {
                __gl_DebugInfo SetData(0, size);
            }

            __forceinline void SetData(void const *data, u32 size)
            {
                __gl_DumpError glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
            }

            __forceinline void SetData(void const *data, u32 offset, u32 size)
            {
                __gl_DumpError glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
            }

            __forceinline void GetData(void *data, u32 size)
            {
                __gl_DumpError glGetBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
            }

            __forceinline void GetData(void *data, u32 offset, u32 size)
            {
                __gl_DumpError glGetBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
            }

            __forceinline void SetTexCoordPointer(u32 size, u32 type, u32 stride, u32 offset, bool enable = true)
            {
                __gl_DumpError glTexCoordPointer(GLint(size), GLenum(type), GLsizei(stride), (GLvoid const *)offset);
                if (enable) glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            }

            __forceinline void SetColorPointer(u32 size, u32 type, u32 stride, u32 offset, bool enable = true)
            {
                __gl_DumpError glColorPointer(GLint(size), GLenum(type), GLsizei(stride), (GLvoid const *)offset);
                if (enable) glEnableClientState(GL_COLOR_ARRAY);
            }

            __forceinline void SetNormalPointer(u32 type, u32 stride, u32 offset, bool enable = true)
            {
                __gl_DumpError glNormalPointer(GLenum(type), GLsizei(stride), (GLvoid const *)offset);
                if (enable) glEnableClientState(GL_NORMAL_ARRAY);
            }

            __forceinline void SetVertexPointer(u32 size, u32 type, u32 stride, u32 offset, bool enable = true)
            {
                __gl_DumpError glVertexPointer(GLint(size), GLenum(type), GLsizei(stride), (GLvoid const *)offset);
                if (enable) glEnableClientState(GL_VERTEX_ARRAY);
            }

            __forceinline void SetVertexAttribPointer(u32 id, u32 size, u32 type, bool normalized, u32 stride, u32 offset, bool enable = true)
            {
                __gl_DumpError glVertexAttribPointer(GLuint(id), GLint(size), GLenum(type), GLboolean(normalized), GLsizei(stride), (GLvoid const *)offset);
                if (enable) glEnableVertexAttribArray(GLuint(id));
            }

            __forceinline void SetTexCoordPointer()
            {
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            }

            __forceinline void SetColorPointer()
            {
                glEnableClientState(GL_COLOR_ARRAY);
            }

            __forceinline void SetNormalPointer()
            {
                glEnableClientState(GL_NORMAL_ARRAY);
            }

            __forceinline void SetVertexPointer()
            {
                glEnableClientState(GL_VERTEX_ARRAY);
            }

            __forceinline void SetVertexAttribPointer(u32 id)
            {
                glEnableVertexAttribArray(GLuint(id));
            }

            __forceinline void UnsetTexCoordPointer()
            {
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            }

            __forceinline void UnsetColorPointer()
            {
                glDisableClientState(GL_COLOR_ARRAY);
            }

            __forceinline void UnsetNormalPointer()
            {
                glDisableClientState(GL_NORMAL_ARRAY);
            }

            __forceinline void UnsetVertexPointer()
            {
                glDisableClientState(GL_VERTEX_ARRAY);
            }

            __forceinline void UnsetVertexAttribPointer(u32 id)
            {
                glDisableVertexAttribArray(GLuint(id));
            }

            __forceinline void DrawPrimitiveArray(u32 type, u32 count)
            {
                assert(type < 7);

                static GLuint prim[8] = { GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN };

                if (type == 6)
                {
                    __gl_DumpError glDrawRectangleArrays(count/4);
                }
                else
                {
                    __gl_DumpError glDrawArrays(prim[type], 0, count);
                }
            }
        };
    }
}

#endif // hal_ogl_vbo_h__
