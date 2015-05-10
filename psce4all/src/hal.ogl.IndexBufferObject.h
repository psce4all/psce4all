#ifndef hal_ogl_IndexBufferObject_h__
#define hal_ogl_IndexBufferObject_h__

#include "hal.ogl.BufferObject.h"

namespace hal
{
    namespace ogl
    {
        class IndexBufferObject : public BufferObject< GL_ELEMENT_ARRAY_BUFFER >
        {
        public:
            IndexBufferObject()
            {
            }

            ~IndexBufferObject()
            {
            }

            using BufferObject< GL_ELEMENT_ARRAY_BUFFER >::Create;
            using BufferObject< GL_ELEMENT_ARRAY_BUFFER >::Delete;
            using BufferObject< GL_ELEMENT_ARRAY_BUFFER >::Bind;
            using BufferObject< GL_ELEMENT_ARRAY_BUFFER >::Unbind;
            using BufferObject< GL_ELEMENT_ARRAY_BUFFER >::Map;
            using BufferObject< GL_ELEMENT_ARRAY_BUFFER >::Unmap;

            __forceinline void Bind(void const *data, u32 size)
            {
                __gl_DebugInfo Bind();
                __gl_DumpError glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
            }

            __forceinline void Bind(u32 size)
            {
                __gl_DebugInfo Bind(0, size);
            }

            __forceinline void SetData(u32 size)
            {
                __gl_DebugInfo SetData(0, size);
            }

            __forceinline void SetData(void const *data, u32 size)
            {
                __gl_DumpError glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
            }
        };
    }
}
#endif // hal_ogl_IndexBufferObject_h__
