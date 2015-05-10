#ifndef hal_ogl_Program_h__
#define hal_ogl_Program_h__

#include "hal.ogl.Core.h"

namespace hal
{
    namespace ogl
    {
        class Program : protected hal::ogl::Core
        {
        public:

            Program() : m_id(0), m_binary(0)
            {
            }

            Program(GLuint id, u32 binary = 0) : m_id(id), m_binary(binary)
            {
            }

            ~Program()
            {
                assert(("Program is not deleted", (m_id == 0)));
            }

            /*__forceinline*/ void Create()
            {
                assert(("Program is already created", (m_id == 0)));

                __gl_DumpError m_id = glCreateProgram();
            }

            /*__forceinline*/ void Delete()
            {
                assert(("Program is already deleted", (m_id != 0)));

                __gl_DumpError glDeleteProgram(m_id);

                m_id = 0;
            }


            /*__forceinline*/ void Bind()
            {
                assert(("Program is not valid", (m_id != 0)));

                __gl_DumpError glUseProgram(m_id);
            }

            /*__forceinline*/ void Unbind()
            {
                __gl_DumpError glUseProgram(0);
            }

            /*__forceinline*/ void Attach(GLuint shader_id)
            {
                assert(("Program is not valid", (m_id != 0)));

                __gl_DumpError glAttachShader(m_id, shader_id);
            }

            /*__forceinline*/ void Detach(GLuint shader_id)
            {
                assert(("Program is not valid", (m_id != 0)));

                __gl_DumpError glDetachShader(m_id, shader_id);
            }

            /*__forceinline*/ bool LoadBinary(char const * binary)
            {
                assert(("Program is not valid", (m_id != 0)));

                if (!m_binary)
                {
                    __gl_DumpError glProgramParameteri(m_id, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);

                    m_binary = true;
                }

                __gl_DumpError glProgramBinary(m_id, *((GLenum*)(binary + sizeof(GLsizei))), (void*)(binary + sizeof(GLsizei) + sizeof(GLenum)), *((GLsizei*)(binary)));

                return CheckStatus(true);
            }

            /*__forceinline*/ char const * SaveBinary(GLsizei & size)
            {
                if (m_id)
                {
                    __gl_DumpError glGetProgramiv(m_id, PROGRAM_BINARY_LENGTH, &size);

                    char const *binary = new char[size + sizeof(GLsizei) + sizeof(GLenum)];

                    __gl_DumpError glGetProgramBinary(m_id, size, (GLsizei*)(binary), (GLenum*)(binary + sizeof(GLsizei)), (void*)(binary + sizeof(GLsizei) + sizeof(GLenum)));

                    size += sizeof(GLsizei) + sizeof(GLenum);

                    return binary;
                }

                return 0;
            }

            /*__forceinline*/ bool Link()
            {
                assert(("Program is not valid", (m_id != 0)));

                if (!m_binary)
                {
                    __gl_DumpError glProgramParameteri(m_id, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);

                    m_binary = true;
                }

                __gl_DumpError glLinkProgram(m_id);

                return CheckStatus(false);
            }

            /*__forceinline*/ GLint GetUniformLocation(char const *name) const
            {
                assert(("Program is not valid", (m_id != 0)));

                GLint result;

                __gl_DumpError result = Core::GetUniformLocation(m_id, name);

                return result;
            }

            /*__forceinline*/ void TransformFeedbackVaryings(GLsizei count, const GLchar ** varyings, GLenum buffer_mode)
            {
                __gl_DumpError Core::TransformFeedbackVaryings(m_id, count, varyings, buffer_mode);
            }

            /*__forceinline*/ GLuint GetSubroutineIndex(GLenum shader_type, char const *name) const
            {
                assert(("Program is not valid", (m_id != 0)));

                GLint result;

                __gl_DumpError result = glGetSubroutineIndex(m_id, shader_type, name);

                return result;
            }

            /*__forceinline*/ GLint GetSubroutineUniformLocation(GLenum shader_type, char const *name) const
            {
                assert(("Program is not valid", (m_id != 0)));

                GLint result;

                __gl_DumpError result = glGetSubroutineUniformLocation(m_id, shader_type, name);

                return result;
            }

            /*__forceinline*/ void UniformSubroutines(GLenum shader_type, GLsizei count, const GLuint * indices)
            {
                __gl_DumpError glUniformSubroutinesuiv(shader_type, count, indices);
            }

            static class Null : protected Core
            {
            public:
                static /*__forceinline*/ void Bind()
                {
                    __gl_DumpError glUseProgram(0);
                }
            } null;

            __forceinline void SetId(GLuint id, u32 binary = 0)
            {
                m_id        = id;
                m_binary    = binary;
            }

            __forceinline GLuint Id() const
            {
                return m_id;
            }

        protected:
            GLuint          m_id;
            u32             m_separable : 1;
            u32             m_binary    : 1;
            static GLenum   m_binary_format;
            static GLsizei  m_binary_length;

            __noinline bool CheckStatus(bool loading)
            {
                GLint result = GL_FALSE;

                glGetProgramiv(m_id, GL_LINK_STATUS, &result);

                if (result == GL_FALSE)
                {
                    int info_log_length;
                    glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &info_log_length);

                    char * buffer = (char *)alloca(info_log_length);

                    glGetProgramInfoLog(m_id, info_log_length, NULL, buffer);

                    errorf(ogl, "%s program... %s\n", (loading ? "Loading" : "Linking"), buffer);
                    if (Core::__this_debuginfo__)
                    {
                        Core::__this_debuginfo__->Dump();
                    }

                    return false;
                }

                return true;
            }

        };
    }
}

#endif // hal_ogl_Program_h__


