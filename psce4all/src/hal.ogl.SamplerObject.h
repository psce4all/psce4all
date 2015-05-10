#ifndef hal_ogl_SamplerObject_h__
#define hal_ogl_SamplerObject_h__

#include "hal.ogl.DeletableObject.h"

namespace hal
{
    namespace ogl
    {
        class SamplerObject : protected DeletableObject
        {
        public:
            SamplerObject()
            {
            }

            SamplerObject(GLuint id) : DeletableObject(id)
            {
            }

            ~SamplerObject()
            {
            }

            void Create()
            {
                __gl_DebugInfo AssertCreate([](DeletableObject * that){ __gl_DumpError glGenSamplers(1, &(that->m_id)); });
            }

            void Delete()
            {
                __gl_DebugInfo AssertDelete([](DeletableObject * that){ __gl_DumpError glDeleteSamplers(1, &(that->m_id)); });
            }

            void Bind(u32 index)
            {
                __gl_DumpError glBindSampler(index, m_id);
            }

            void Unbind(u32 index)
            {
                __gl_DumpError glBindSampler(index, 0);
            }

            void SetAnisotropicFiltering(f32 value = 1.0f)
            {
                static f32 max_anisotropy = GetMaxAnisotropy();

                glSamplerParameterf(m_id, GL_TEXTURE_MAX_ANISOTROPY_EXT, max(1.0f, min(value, max_anisotropy)));
            }

            void UnsetAnisotropicFiltering()
            {
                glSamplerParameterf(m_id, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0.0f);
            }

            f32  GetMaxAnisotropy()
            {
                f32 result = 1.0;
                glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &result);
                return result;
            }

            void SetWrap(bool wrap_s, bool wrap_t)
            {
                glSamplerParameterf(m_id, GL_TEXTURE_WRAP_S, wrap_s ? GL_REPEAT : GL_CLAMP_TO_EDGE);
                glSamplerParameterf(m_id, GL_TEXTURE_WRAP_T, wrap_t ? GL_REPEAT : GL_CLAMP_TO_EDGE);
            }

            void SetFiltering(u32 min_filter, bool mag_filter)
            {
                switch (min_filter)
                {
                case 0: glSamplerParameterf(m_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);                break;
                case 1: glSamplerParameterf(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);                 break;
                case 4: glSamplerParameterf(m_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); break;
                case 5: glSamplerParameterf(m_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);  break;
                case 6: glSamplerParameterf(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);  break;
                case 7: glSamplerParameterf(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);   break;
                }
                glSamplerParameterf(m_id, GL_TEXTURE_MAG_FILTER, mag_filter ? GL_LINEAR : GL_NEAREST);
            }

            void SetFiltering(bool wrap_s, bool wrap_t, u32 min_filter, bool mag_filter)
            {
                SetWrap(wrap_s, wrap_t);
                SetFiltering(min_filter, mag_filter);
            }

            void SetBorderColor(f32 color[])
            {
                glSamplerParameterfv(m_id, GL_TEXTURE_BORDER_COLOR, color);
            }

            void SetLOD(f32 min, f32 max, f32 bias)
            {
                glSamplerParameterf(m_id, GL_TEXTURE_MIN_LOD,  min);
                glSamplerParameterf(m_id, GL_TEXTURE_MAX_LOD,  max);
                glSamplerParameterf(m_id, GL_TEXTURE_LOD_BIAS, bias);
            }

            operator GLuint() const
            {
                return m_id;
            }

            using DeletableObject::Id;
            using DeletableObject::Deletable;
        };
    }
}

#endif // gl_SamplerObject_h__
