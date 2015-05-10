#ifndef hal_ogl_SeparateProgram_h__
#define hal_ogl_SeparateProgram_h__

#include "hal.ogl.Shader.h"
#include "hal.ogl.Program.h"

namespace hal
{
    namespace ogl
    {
        class SeparateProgram : public Program
        {
        public:
            SeparateProgram(GLenum type = 0)
            :   Program(0, 0), m_type(type)
            {
            }

            SeparateProgram(GLuint id, GLenum type = 0)
            :   Program(id, 0), m_type(type)
            {
            }

            ~SeparateProgram()
            {
            }

            __forceinline void Create(GLenum type)
            {
                __gl_DebugInfo Program::Create();
                __gl_DummyInfo m_type = type;
            }

            __forceinline void Create(GLenum type, char const * source)
            {
                assert(("Separate program is already created", (m_id == 0)));

                __gl_DumpError m_id   = glCreateShaderProgramv(type, 1, &source);
                __gl_DummyInfo m_type = type;

                CheckStatus(true);
            }

            __forceinline void Create(GLenum type, char const * source[], u32 count)
            {
                assert(("Separate program is already created", (m_id == 0)));

                __gl_DumpError m_id   = glCreateShaderProgramv(type, count, source);
                __gl_DummyInfo m_type = type;
            }

            __forceinline void SetId(GLuint id)
            {
                m_id = id;
            }

            __forceinline void SetType(GLenum type)
            {
                assert(("Separate program is already created", (m_id == 0)));

                m_type = type;
            }

            __forceinline GLuint Id() const
            {
                return m_id;
            }

            __forceinline GLenum Type() const
            {
                return m_type;
            }

        protected:
            GLenum m_type;

        private:
            using Program::Create;
            using Program::Attach;
            using Program::Detach;
            using Program::Link;

            __forceinline bool AttachSource(char const * source[], u32 count)
            {
                assert(("Separate program is not valid", (m_id != 0)));

                Shader shader(m_type);

                bool result;

                __gl_DebugInfo result = shader.Compile(source, count);

                if (result)
                {
                    __gl_DebugInfo Attach(shader.Id());
                }

                return result;
            }
        };

        class VertexProgram : public SeparateProgram
        {
        public:
            __forceinline void Create()
            {
                __gl_DebugInfo SeparateProgram::Create(GL_VERTEX_SHADER);
            }

        private:
            void SetType(GLenum type);
        };

        class GeometryProgram : public SeparateProgram
        {
        public:
            __forceinline void Create()
            {
                __gl_DebugInfo SeparateProgram::Create(GL_GEOMETRY_SHADER);
            }

        private:
            void SetType(GLenum type);
        };

        class FragmentProgram : public SeparateProgram
        {
        public:
            __forceinline void Create()
            {
                __gl_DebugInfo SeparateProgram::Create(GL_FRAGMENT_SHADER);
            }

        private:
            void SetType(GLenum type);
        };
    }
}

#endif // gl_SeparateProgram_h__


