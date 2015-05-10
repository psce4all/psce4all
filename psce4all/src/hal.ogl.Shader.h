#ifndef hal_ogl_shader_h__
#define hal_ogl_shader_h__

#include "hal.ogl.Core.h"

namespace hal
{
    namespace ogl
    {
        class Shader : protected Core
        {
        public:
            Shader(GLenum type = 0)
            :   m_id(0), m_type(type)
            {
            }

            Shader(GLuint id, GLenum type)
            :   m_id(id), m_type(type)
            {
            }

            ~Shader()
            {
                __gl_DebugInfo Delete();
            }

            __forceinline void Delete()
            {
                if (m_id)
                {
                    __gl_DumpError glDeleteShader(m_id);

                    m_id = 0;
                }
            }

            __forceinline void SetId(GLuint id)
            {
                m_id = id;
            }

            __forceinline void SetType(GLenum type)
            {
                assert(m_id == 0);

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

            /*__forceinline*/ bool Compile(char const * source)
            {
                __gl_DumpError m_id = glCreateShader(m_type);

                __gl_DumpError glShaderSource(m_id, 1, &source, NULL);

                __gl_DumpError glCompileShader(m_id);

                return CheckStatus();
            }

            /*__forceinline*/ bool Compile(char const * source[], u32 count)
            {
                __gl_DumpError m_id = glCreateShader(m_type);

                __gl_DumpError glShaderSource(m_id, count, source, NULL);

                __gl_DumpError glCompileShader(m_id);

                return CheckStatus();
            }

        protected:
            GLuint m_id;
            GLenum m_type;

        private:
            __noinline bool CheckStatus()
            {
                GLint result = GL_FALSE;

                glGetShaderiv(m_id, GL_COMPILE_STATUS, &result);

                if (result == GL_FALSE)
                {
                    int info_log_length;
                    glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &info_log_length);

                    char * buffer = (char *)alloca(info_log_length);

                    glGetShaderInfoLog(m_id, info_log_length, NULL, buffer);

                    errorf(ogl, "Compiling shader...\n%s\n", buffer);
                    if (Core::__this_debuginfo__)
                    {
                        Core::__this_debuginfo__->Dump();
                    }

                    return false;
                }

                return true;
            }
        };

        class VertexShader : public Shader
        {
        public:
            VertexShader() : Shader(0, VERTEX_SHADER)
            {
            }

            VertexShader(GLuint id) : Shader(id, VERTEX_SHADER)
            {
            }

        private:
            void SetType(GLenum type);
        };

        class GeometryShader : public Shader
        {
        public:
            GeometryShader() : Shader(0, GEOMETRY_SHADER)
            {
            }

            GeometryShader(GLuint id) : Shader(id, GEOMETRY_SHADER)
            {
            }

        private:
            void SetType(GLenum type);
        };

        class FragmentShader : public Shader
        {
        public:
            FragmentShader() : Shader(0, FRAGMENT_SHADER)
            {
            }

            FragmentShader(GLuint id) : Shader(id, FRAGMENT_SHADER)
            {
            }

        private:
            void SetType(GLenum type);
        };
    }
}
#endif // gl_shader_h__


