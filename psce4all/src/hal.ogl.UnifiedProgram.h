#ifndef hal_ogl_UnifiedProgram_h__
#define hal_ogl_UnifiedProgram_h__

#include "hal.ogl.Shader.h"
#include "hal.ogl.Program.h"

namespace hal
{
    namespace ogl
    {
        class UnifiedProgram : public Program
        {
        public:
            UnifiedProgram() : Program()
            {
            }

            __forceinline bool CompileVertex(char const *source)
            {
                bool result;
                __gl_DebugInfo result = CompileVertex(&source, 1);
                return result;
            }

            __forceinline bool CompileGeometry(char const *source)
            {
                bool result;
                __gl_DebugInfo result = CompileGeometry(&source, 1);
                return result;
            }

            __forceinline bool CompileFragment(char const *source)
            {
                bool result;
                __gl_DebugInfo result = CompileFragment(&source, 1);
                return result;
            }

            __forceinline bool CompileVertex(char const *source[], u32 count)
            {
                bool result;
                __gl_DebugInfo result = AttachSource(VERTEX_SHADER, source, count);
                return result;
            }

            __forceinline bool CompileGeometry(char const *source[], u32 count)
            {
                bool result;
                __gl_DebugInfo result = AttachSource(GEOMETRY_SHADER, source, count);
                return result;
            }

            __forceinline bool CompileFragment(char const *source[], u32 count)
            {
                bool result;
                __gl_DebugInfo result = AttachSource(FRAGMENT_SHADER, source, count);
                return result;
            }

        private:
            __forceinline bool AttachSource(GLenum type, char const *source[], u32 count)
            {
                Shader shader(type);

                __gl_DebugInfo if (shader.Compile(source, count))
                {
                    __gl_DebugInfo Attach(shader.Id());

                    return true;
                }

                return false;
            }
        };
    }
}

#endif // hal_ogl_UnifiedProgram_h__

