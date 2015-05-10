#ifndef hal_ogl_Subroutine_h__
#define hal_ogl_Subroutine_h__

#include "hal.ogl.Core.h"
#include "hal.ogl.Program.h"

namespace hal
{
    namespace ogl
    {
#if 0
        template< int count >
        class Subroutine : protected Core
        {
        public:
            Subroutine(GLint id = -1) : m_id(id), m_program(0), m_shader(0)
            {
                memset(m_id_array, 0, sizeof(m_id_array));
            }

            ~Subroutine()
            {
            }

            operator GLint const () const
            {
                return m_id;
            }

            void Bind(Program & program, GLenum shader)
            {
                m_program = &program;
                m_shader  = shader;
            }

            void Register(char const * name[count])
            {
                for (int i = 0; i < count; ++i)
                {
                    __gl_debuginfo m_id_array[i] = m_program.GetSubroutineIndex(m_shader, name[i]);
                }
            }

            void Register(int i, char const name[])
            {
                __gl_debuginfo m_id_array[i] = m_program.GetSubroutineIndex(m_shader, name);
            }

            void operator = (GLint id)
            {
                if (id != m_id)
                {
                    __gl_debuginfo program.UniformSubroutinesuiv(m_shader, 1, m_id_array + m_id);
                    m_id = id;
                }
            }

            void Apply(Program & program, GLenum shader, char const name[])
            {
            }

            GLint     m_id;
            GLint     m_id_array[count];
            Program * m_program;
            GLenum    m_shader;
        };
#endif
    }
}

#endif // gl_Subroutine_h__
