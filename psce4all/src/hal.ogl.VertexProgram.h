#ifndef hal_ogl_VertexProgram_h__
#define hal_ogl_VertexProgram_h__

#include "hal.ogl.SeparateProgram.h"

namespace hal
{
    namespace ogl
    {
        template< > class SeparateProgram< GL_VERTEX_SHADER > : public SeparateProgram< 0 >
        {
        };

        typedef SeparateProgram< GL_VERTEX_SHADER > VertexProgram;
    }
}

#endif // hal_ogl_VertexProgram_h__


