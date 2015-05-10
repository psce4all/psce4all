#ifndef hal_ogl_BufferObject_h__
#define hal_ogl_BufferObject_h__

#include "hal.ogl.DeletableObject.h"

namespace hal
{
    namespace ogl
    {
        template< GLenum type > class BufferObject : protected DeletableObject
        {
        public:
            BufferObject()
            {
            }

            BufferObject(GLuint id) : DeletableObject(id)
            {
            }

            ~BufferObject()
            {
            }

            void Create()
            {
                __gl_DebugInfo AssertCreate([](DeletableObject * that){ __gl_DumpError glGenBuffers(1, &(that->m_id)); });
            }

            void Delete()
            {
                __gl_DebugInfo AssertDelete([](DeletableObject * that){ __gl_DumpError glDeleteBuffers(1, &(that->m_id)); });
            }

            __forceinline void AliasId(BufferObject &vbo)
            {
                m_id = vbo.m_id;
            }

            __forceinline void SwapId(BufferObject &vbo)
            {
                GLuint swapped_id = m_id;
                m_id              = vbo.m_id;
                vbo.m_id          = swapped_id;
            }

            __forceinline void SwapDeletable(BufferObject &vbo)
            {
                GLuint swapped_deletable = m_deletable;
                m_deletable              = vbo.m_deletable;
                vbo.m_deletable          = swapped_deletable;
            }

            __forceinline void Swap(BufferObject &vbo)
            {
                SwapId(vbo);
                SwapDeletable(vbo);
            }

            __forceinline GLuint Bind()
            {
                __gl_DumpError glBindBuffer(type, m_id);

                return m_id;
            }

            __forceinline GLuint Unbind()
            {
                __gl_DebugInfo glBindBuffer(type, 0);

                return 0;
            }

            __forceinline void * Map(u32 size)
            {
                __gl_DumpError glBufferData(type, size, 0, DYNAMIC_DRAW);
                __gl_DumpError return (void *)glMapBuffer(type, WRITE_ONLY);
            }

            __forceinline void Unmap()
            {
                __gl_DumpError glUnmapBuffer(type);
            }

            using DeletableObject::Id;
            using DeletableObject::Deletable;
        };
    }
}


#endif // hal_ogl_BufferObject_h__
