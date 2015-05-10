#ifndef hal_ogl_fbo_h__
#define hal_ogl_fbo_h__

#include "hal.ogl.Core.h"

namespace hal
{
    namespace ogl
    {
        class FrameBufferObject : protected Core
        {
        public:
            FrameBufferObject() : m_id(0), m_target(0)
            {
            }

            ~FrameBufferObject()
            {
                assert(("Frame object is not deleted", (m_id == 0)));
            }

            __forceinline GLuint Id() const
            {
                return m_id;
            }

            /*__forceinline*/ void Create()
            {
                assert(("Frame object is already created", (m_id == 0)));

                __gl_DumpError glGenFramebuffers(1, &m_id);
            }

            __forceinline void Delete()
            {
                assert(("Frame object is already deleted", (m_id != 0)));

                __gl_DumpError glDeleteFramebuffers(1, &m_id);

                m_id = 0;
            }

            /*__forceinline*/ void Bind(GLenum target)
            {
                __gl_DumpError glBindFramebuffer(target, m_id);
                m_target = target;
            }

            __forceinline void Unbind()
            {
                __gl_DumpError glBindFramebuffer(m_target, 0);
            }

            /*__forceinline*/ void AttachTexture2D(GLenum attachment, GLenum target, GLuint texture, GLint level)
            {
                __gl_DumpError glFramebufferTexture2D(m_target, attachment, target, texture, level);
            }

            __forceinline void AttachRenderbuffer(GLenum attachment, GLuint renderbuffer)
            {
                __gl_DumpError glFramebufferRenderbuffer(m_target, attachment, RENDERBUFFER, renderbuffer);
            }

            /*__forceinline*/ bool CheckStatus()
            {
                GLenum status;

                __gl_DumpError status = glCheckFramebufferStatus(m_target);

                switch (status)
                {
                case GL_FRAMEBUFFER_COMPLETE_EXT:
                    tracef(ogl, "Framebuffer complete.");
                    return true;

                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
                    errorf(ogl, "Framebuffer incomplete: Attachment is NOT complete.");
                    break;

                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
                    errorf(ogl, "Framebuffer incomplete: No image is attached to FBO.");
                    break;

                case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
                    errorf(ogl, "Framebuffer incomplete: Attached images have different dimensions.");
                    break;

                case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
                    errorf(ogl, "Framebuffer incomplete: Color attached images have different internal formats.");
                    break;

                case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
                    errorf(ogl, "Framebuffer incomplete: Draw buffer.");
                    break;

                case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
                    errorf(ogl, "Framebuffer incomplete: Read buffer.");
                    break;

                case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
                    errorf(ogl, "Unsupported by FBO implementation.");
                    break;

                default:
                    errorf(ogl, "Unknown error.");
                    break;
                }

                if (Core::__this_debuginfo__)
                {
                    Core::__this_debuginfo__->Dump();
                }

                return false;
            }

        private:
            GLuint m_id;
            GLenum m_target;

        /*
            static GLboolean IsRenderbuffer(GLuint renderbuffer);
            static void      BindRenderbuffer(GLenum target, GLuint renderbuffer);
            static void      DeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers);
            static void      GenRenderbuffers(GLsizei n, GLuint *renderbuffers);

            static void      RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);

            static void      RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);

            static void      GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params);

            static boolean   IsFramebuffer(GLuint framebuffer);
            static void      BindFramebuffer(GLenum target, GLuint framebuffer);
            static void      DeleteFramebuffers(GLsizei n, const GLuint *framebuffers);
            static void      GenFramebuffers(GLsizei n, GLuint *framebuffers);

            static GLenum    CheckFramebufferStatus(GLenum target);

            static void      FramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
            static void      FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
            static void      FramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint layer);
            static void      FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);

            static void      FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);

            static void      GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint *params);

            static void      BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);

            static void      GenerateMipmap(GLenum target);
        */
        };
    }
}

#endif // hal_ogl_fbo_h__
