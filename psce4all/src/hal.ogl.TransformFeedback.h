#ifndef hal_ogl_TransformFeedback_h__
#define hal_ogl_TransformFeedback_h__

#include "hal.ogl.DeletableObject.h"

namespace hal
{
    namespace ogl
    {
        class TransformFeedback : protected DeletableObject
        {
        public:
            TransformFeedback(GLuint id = 0) : DeletableObject(id)
            {
            }

            ~TransformFeedback()
            {
            }

            void Create()
            {
                __gl_DebugInfo AssertCreate([](DeletableObject * that){ __gl_DumpError glGenQueries(1, &(that->m_id)); });
            }

            void Delete()
            {
                __gl_DebugInfo AssertDelete([](DeletableObject * that){ __gl_DumpError glDeleteQueries(1, &(that->m_id)); });
            }

            void Begin(GLenum mode)
            {
                __gl_DumpError glBeginTransformFeedback(mode);
                //glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, m_id);

                //CheckError(__FUNCSIG__, __LINE__);
            }

            void End()
            {
                __gl_DumpError glEndTransformFeedback();

                //glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
            }

            void SuspendRasterizer()
            {
                __gl_DumpError glEnable(GL_RASTERIZER_DISCARD);
            }

            void ResumeRasterizer()
            {
                __gl_DumpError glDisable(GL_RASTERIZER_DISCARD);
            }

            void BufferBase(GLuint index, GLuint vbo)
            {
                __gl_DumpError glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, index, vbo);
            }

            u32 GetPrimitivesWritten() const
            {
                GLuint result;

                __gl_DumpError glGetQueryObjectuiv(m_id, GL_QUERY_RESULT, &result);

                return u32(result);
            }

            using Core::DrawArrays;
            using Core::DrawElements;

            using DeletableObject::Id;
            using DeletableObject::Deletable;
        };
    }
}
#endif // hal_ogl_TransformFeedback_h__
