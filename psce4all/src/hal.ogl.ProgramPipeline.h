#ifndef hal_ogl_ProgramPipeline_h__
#define hal_ogl_ProgramPipeline_h__

#include "hal.ogl.Core.h"

namespace hal
{
     namespace ogl
     {
         class ProgramPipelines : protected Core
         {
         public:

             ProgramPipelines() : m_id(0)
             {
             }

             ProgramPipelines(GLuint id) : m_id(id)
             {
             }

             ~ProgramPipelines()
             {
                 assert(("Program pipelines are not deleted", (m_id == 0)));
             }

             __forceinline GLuint Id() const
             {
                 return m_id;
             }

             __forceinline void Create()
             {
                 assert(("Program pipelines are already created", (m_id == 0)));

                 __gl_DumpError glGenProgramPipelines(1, &m_id);
             }

             __forceinline void Delete()
             {
                 assert(("Program pipelines are already deleted", (m_id != 0)));
                 {
                     __gl_DebugInfo Unbind();

                     __gl_DumpError glDeleteProgramPipelines(1, &m_id);

                     m_id = 0;
                 }
             }

             __forceinline void Bind()
             {
                 assert(m_id != 0);

                 __gl_DumpError glBindProgramPipeline(m_id);
             }

             __forceinline void Unbind()
             {
                 __gl_DumpError glBindProgramPipeline(0);
             }

             __forceinline void UseProgramStages(GLbitfield stages, GLuint program_id)
             {
                 assert(("Program pipelines are not valid", (m_id != 0)));

                 __gl_DumpError glUseProgramStages(m_id, stages, program_id);
             }

             __forceinline void UseVertexProgram(GLuint program_id)
             {
                 __gl_DebugInfo UseProgramStages(GL_VERTEX_SHADER_BIT, program_id);
             }

             __forceinline void UseGeometryProgram(GLuint program_id)
             {
                 __gl_DebugInfo UseProgramStages(GL_GEOMETRY_SHADER_BIT, program_id);
             }

             __forceinline void UseFragmentProgram(GLuint program_id)
             {
                 __gl_DebugInfo UseProgramStages(GL_FRAGMENT_SHADER_BIT, program_id);
             }

             __forceinline void UnuseProgramStages(GLbitfield stages)
             {
                 __gl_DebugInfo UseProgramStages(stages, 0);
             }

         protected:
             GLuint          m_id;
         };
     }
}

#endif // hal_ogl_ProgramPipeline_h__


