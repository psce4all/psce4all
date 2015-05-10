#ifndef hal_ogl_OcclusionQuery_h__
#define hal_ogl_OcclusionQuery_h__

#include "hal.ogl.Core.h"

namespace hal
{
    namespace ogl
    {
        class OcclusionQuery : public Core
        {
        public:
            OcclusionQuery() : m_oq(-1)
            {
                __gl_DumpError glGenQueries(1, (GLuint *)&m_oq);
            }

            ~OcclusionQuery()
            {
                __gl_DumpError glDeleteQueries(1, (GLuint *)&m_oq);
            }

            __forceinline void BeginBBOX()
            {
                __gl_DumpError glPushAttrib(GL_ENABLE_BIT|GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

                __gl_DumpError glColorMask(false, false, false, false);
                __gl_DumpError glDepthMask(false);

                __gl_DumpError glDisable(GL_BLEND);
                __gl_DumpError glDisable(GL_STENCIL_TEST);
                __gl_DumpError glDisable(GL_LIGHTING);
                __gl_DumpError glDisable(GL_TEXTURE_2D);
                __gl_DumpError glDisable(GL_ALPHA_TEST);
                __gl_DumpError glDisable(GL_FOG);
                __gl_DumpError glDisable(GL_DEPTH_TEST);
                __gl_DumpError glDisable(GL_LOGIC_OP);
                __gl_DumpError glDisable(GL_CULL_FACE);
                __gl_DumpError glDisable(GL_SCISSOR_TEST);

                __gl_DumpError glBeginQuery(GL_SAMPLES_PASSED, m_oq);

                __gl_DumpError glBegin(GL_QUADS);
            }

            __forceinline void AddBBOX(f32 bbox[8][3])
            {
                // Front face
                glVertex3fv(bbox[0]);
                glVertex3fv(bbox[1]);
                glVertex3fv(bbox[3]);
                glVertex3fv(bbox[2]);

                // Back face
                glVertex3fv(bbox[4]);
                glVertex3fv(bbox[5]);
                glVertex3fv(bbox[7]);
                glVertex3fv(bbox[6]);

                // Right face
                glVertex3fv(bbox[1]);
                glVertex3fv(bbox[5]);
                glVertex3fv(bbox[7]);
                glVertex3fv(bbox[3]);

                // Left face
                glVertex3fv(bbox[0]);
                glVertex3fv(bbox[4]);
                glVertex3fv(bbox[6]);
                glVertex3fv(bbox[2]);

                // Top face
                glVertex3fv(bbox[2]);
                glVertex3fv(bbox[3]);
                glVertex3fv(bbox[7]);
                glVertex3fv(bbox[6]);

                // Bottom face
                glVertex3fv(bbox[0]);
                glVertex3fv(bbox[1]);
                glVertex3fv(bbox[5]);
                glVertex3fv(bbox[4]);
            }

            __forceinline void EndBBOX()
            {
                __gl_DumpError glEnd();

                __gl_DumpError glEndQuery(GL_SAMPLES_PASSED);

                __gl_DumpError glFlush();
                __gl_DumpError glPopAttrib();
            }

            __forceinline bool IsOccluded()
            {
                int result = 0;
                __gl_DumpError glGetQueryObjectiv(m_oq, GL_QUERY_RESULT, &result);
                return (0 == result);
            }

        private:
            GLuint m_oq;
        };
    }
}

#endif // hal_ogl_OcclusionQuery_h__