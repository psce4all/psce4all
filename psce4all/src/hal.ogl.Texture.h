#ifndef hal_ogl_Texture_h__
#define hal_ogl_Texture_h__

#include "hal.ogl.DeletableObject.h"
#include "hal.ogl.States.h"

namespace hal
{
    namespace ogl
    {
        class Texture : protected DeletableObject
        {
        public:
            Texture() : m_target(GL_TEXTURE_2D), m_unit(-1), m_internal_format(GL_RGBA)
            {
            }

            Texture(GLenum target, GLuint id = 0) : DeletableObject(id), m_target(target), m_unit(-1), m_internal_format(GL_RGBA)
            {
            }

            ~Texture()
            {
            }

            void Create()
            {
                __gl_DebugInfo AssertCreate([](DeletableObject * that){ __gl_DumpError glGenTextures(1, &(that->m_id)); });
            }

            void Delete()
            {
                __gl_DebugInfo AssertDelete([](DeletableObject * that){ __gl_DumpError glDeleteTextures(1, &(that->m_id)); });
            }

            void SetInternalFormat(GLenum internal_format)
            {
                m_internal_format = internal_format;
            }

            void Bind(GLenum target)
            {
                __gl_DumpError glBindTexture(target, m_id);

                m_target = target;
            }

            void Unbind()
            {
                __gl_DumpError glBindTexture(m_target, 0);
            }

            void BindImage(GLuint unit, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format)
            {
                __gl_DumpError glBindImageTexture(unit, m_id, level, layered, layer, access, format);

                m_unit = unit;
            }

            void Active(GLuint unit)
            {
                __gl_DumpError glActiveTexture(TEXTURE0 + unit);

                m_unit = unit;
            }

            void SetAnisotropicFiltering(f32 value = 1.0f)
            {
                static f32 max_anisotropy = GetMaxAnisotropy();

                __gl_DumpError glTexParameterf(m_target, GL_TEXTURE_MAX_ANISOTROPY_EXT, max(1.0f, min(value, max_anisotropy)));
            }

            void UnsetAnisotropicFiltering()
            {
                __gl_DumpError glTexParameterf(m_target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0.0f);
            }

            f32  GetMaxAnisotropy()
            {
                f32 result = 1.0;
                __gl_DumpError glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &result);
                return result;
            }

            void SetFiltering(bool wrap_s, bool wrap_t, bool linear_mag, bool linear_min)
            {
                __gl_DumpError glTexParameteri(m_target, GL_TEXTURE_WRAP_S,     wrap_s     ? GL_REPEAT : GL_CLAMP_TO_EDGE);
                __gl_DumpError glTexParameteri(m_target, GL_TEXTURE_WRAP_T,     wrap_t     ? GL_REPEAT : GL_CLAMP_TO_EDGE);
                __gl_DumpError glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, linear_mag ? GL_LINEAR : GL_NEAREST);
                __gl_DumpError glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, linear_min ? GL_LINEAR : GL_NEAREST);
            }

            void SetWrap(bool wrap_s, bool wrap_t)
            {
                __gl_DumpError glTexParameteri(m_target, GL_TEXTURE_WRAP_S, wrap_s ? GL_REPEAT : GL_CLAMP_TO_EDGE);
                __gl_DumpError glTexParameteri(m_target, GL_TEXTURE_WRAP_T, wrap_t ? GL_REPEAT : GL_CLAMP_TO_EDGE);
            }

            void SetLinear(bool linear_mag, bool linear_min)
            {
                __gl_DumpError glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, linear_mag ? GL_LINEAR : GL_NEAREST);
                __gl_DumpError glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, linear_min ? GL_LINEAR : GL_NEAREST);
            }

            void SetMagnifyingFilter(bool linear)
            {
                __gl_DumpError glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, linear ? GL_LINEAR : GL_NEAREST);
            }

            void SetMinimizingFilter(bool linear)
            {
                __gl_DumpError glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, linear ? GL_LINEAR : GL_NEAREST);
            }

            void SetMinimizingFilter(bool linear, bool linear_mipmap)
            {
                __gl_DumpError glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, linear ? (linear_mipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_NEAREST) : (linear_mipmap ? GL_NEAREST_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_NEAREST));
            }

            void SetMinimizingFilter(bool linear, bool linear_mipmap, bool is_mipmap)
            {
                __gl_DumpError glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, is_mipmap ? (linear ? (linear_mipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_NEAREST) : (linear_mipmap ? GL_NEAREST_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_NEAREST)) : (linear ? GL_LINEAR : GL_NEAREST));
            }

            void SetBorderColor(f32 color[])
            {
                __gl_DumpError glTexParameterfv(m_target, GL_TEXTURE_BORDER_COLOR, color);
            }

            void SetBaseLevel(u32 level)
            {
                __gl_DumpError glTexParameteri(m_target, GL_TEXTURE_BASE_LEVEL, level);
            }

            void SetMaxLevel(u32 level)
            {
                __gl_DumpError glTexParameteri(m_target, GL_TEXTURE_MAX_LEVEL, level);
            }

            void SetMinMaxLOD(u32 min_lod, u32 max_lod)
            {
                __gl_DumpError glTexParameteri(m_target, GL_TEXTURE_MIN_LOD, min_lod);
                __gl_DumpError glTexParameteri(m_target, GL_TEXTURE_MAX_LOD, max_lod);
            }

            void SetLODBias(f32 lod_bias)
            {
                __gl_DumpError glTexParameterf(m_target, GL_TEXTURE_LOD_BIAS, lod_bias);
            }

            void SetMaxLODBias(f32 max_lod_bias)
            {
                __gl_DumpError glTexParameterf(m_target, GL_MAX_TEXTURE_LOD_BIAS, max_lod_bias);
            }

            void SetFunction(u32 txf, bool /*rgba*/)
            {
                switch (txf)
                {
                case 0: __gl_DumpError glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); break;
                case 1: __gl_DumpError glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL   ); break;
                case 2: __gl_DumpError glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND   ); break;
                case 3: __gl_DumpError glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE ); break;
                case 4: __gl_DumpError glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD     ); break;
                }
                __gl_DumpError glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE,   1.0f);
                __gl_DumpError glTexEnvf(GL_TEXTURE_ENV, GL_ALPHA_SCALE, 1.0f);
            }

            void SetConstantColor(u32 r, u32 g, u32 b, u32 a)
            {
                f32 rgba[4] = { f32(r)/255.0f, f32(g)/255.0f, f32(b)/255.0f, f32(a)/255.0f };

                __gl_DumpError glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, rgba);
            }

            void SetStorage1D(u32 levels, u32 width)
            {
                __gl_DumpError glTexStorage1D(m_target, levels, m_internal_format, width);

                m_stride = width;
                m_width  = width;
                m_height = 0;
            }

            void SetStorage2D(u32 levels, u32 width, u32 height)
            {
                __gl_DumpError glTexStorage2D(m_target, levels, m_internal_format, width, height);

                m_stride = width;
                m_width  = width;
                m_height = height;
            }

            template< typename Type >
            void LoadImage1D(u32 width, GLenum format, GLenum type, Type const *data, u32 alignment = sizeof(Type))
            {
                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,  alignment);

                __gl_DumpError glTexImage1D(m_target, 0, m_internal_format, width, 0, format, type, (GLvoid const *)data);

                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,  4);

                m_stride = width;
                m_width  = width;
                m_height = 0;
            }

            template< typename Type >
            void LoadImage2D(u32 stride, u32 width, u32 height, GLenum format, GLenum type, Type const *data, u32 alignment = sizeof(Type))
            {
                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,  alignment);
                __gl_DumpError glPixelStorei(GL_UNPACK_ROW_LENGTH, stride);

                __gl_DumpError glTexImage2D(m_target, 0, m_internal_format, width, height, 0, format, type, (GLvoid const *)data);

                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,  4);
                __gl_DumpError glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

                m_stride = stride;
                m_width  = width;
                m_height = height;
            }

            template< typename Type >
            void LoadImage3D(u32 stride, u32 width, u32 height, u32 depth, GLenum format, GLenum type, Type const *data, u32 alignment = sizeof(Type))
            {
                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,    alignment);
                __gl_DumpError glPixelStorei(GL_UNPACK_ROW_LENGTH,   stride);
                __gl_DumpError glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, height);

                __gl_DumpError glTexImage3D(m_target, 0, m_internal_format, width, height, depth, 0, format, type, (GLvoid const *)data);

                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,    4);
                __gl_DumpError glPixelStorei(GL_UNPACK_ROW_LENGTH,   0);
                __gl_DumpError glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, 0);

                m_stride = stride;
                m_width  = width;
                m_height = height;
            }

            template< typename Type >
            void LoadImage2D(u32 level, u32 stride, u32 width, u32 height, GLenum format, GLenum type, Type const *data, u32 alignment = sizeof(Type))
            {
                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,  alignment);
                __gl_DumpError glPixelStorei(GL_UNPACK_ROW_LENGTH, stride);

                __gl_DumpError glTexImage2D(m_target, level, m_internal_format, width, height, 0, format, type, (GLvoid const *)data);

                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,  4);
                __gl_DumpError glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

                m_stride = stride;
                m_width  = width;
                m_height = height;
            }

            template< typename Type >
            void LoadImageDXTn(u32 level, GLenum internal_format, u32 stride, u32 width, u32 height, Type const *data, u32 alignment = sizeof(Type))
            {
                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,  alignment);
                __gl_DumpError glPixelStorei(GL_UNPACK_ROW_LENGTH, stride);

                m_internal_format = internal_format;

                __gl_DumpError glCompressedTexImage2D(m_target, level, m_internal_format, width, height, 0, ((width+3)/4)*((height+3)/4)*4*sizeof(Type), (GLvoid const *)data);

                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,  4);
                __gl_DumpError glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

                m_stride = stride;
                m_width  = width;
                m_height = height;
            }

            template< typename Type >
            void LoadSubImage1D(u32 level, u32 x, u32 width, GLenum format, GLenum type, Type const *data, u32 alignment = sizeof(Type))
            {
                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,  alignment);

                __gl_DumpError glTexSubImage1D(m_target, level, x, width, format, type, (GLvoid const *)data);

                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,  4);
            }

            template< typename Type >
            void LoadSubImage2D(u32 level, u32 stride, u32 x, u32 y, u32 width, u32 height, GLenum format, GLenum type, Type const *data, u32 alignment = sizeof(Type))
            {
                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,  alignment);
                __gl_DumpError glPixelStorei(GL_UNPACK_ROW_LENGTH, stride);

                __gl_DumpError glTexSubImage2D(m_target, level, x, y, width, height, format, type, (GLvoid const *)data);

                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,  4);
                __gl_DumpError glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
            }

            template< typename Type >
            void LoadImage1D(u32 level, u32 skipx, u32 width, GLenum format, GLenum type, Type const *data, u32 alignment = sizeof(Type))
            {
                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,   alignment);
                __gl_DumpError glPixelStorei(GL_UNPACK_SKIP_PIXELS, skipx);

                __gl_DumpError glTexImage1D(m_target, level, m_internal_format, width, 0, format, type, (GLvoid const *)data);

                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,   4);
                __gl_DumpError glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
            }

            template< typename Type >
            void LoadImage2D(u32 level, u32 stride, u32 skipx, u32 skipy, u32 width, u32 height, GLenum format, GLenum type, Type const *data, u32 alignment = sizeof(Type))
            {
                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,   alignment);
                __gl_DumpError glPixelStorei(GL_UNPACK_ROW_LENGTH,  stride);
                __gl_DumpError glPixelStorei(GL_UNPACK_SKIP_PIXELS, skipx);
                __gl_DumpError glPixelStorei(GL_UNPACK_SKIP_ROWS,   skipy);

                __gl_DumpError glTexImage2D(m_target, level, m_internal_format, width, height, 0, format, type, (GLvoid const *)data);

                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,   4);
                __gl_DumpError glPixelStorei(GL_UNPACK_ROW_LENGTH,  0);
                __gl_DumpError glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
                __gl_DumpError glPixelStorei(GL_UNPACK_SKIP_ROWS,   0);
            }

            template< typename Type >
            void LoadSubImage1D(u32 level, u32 skipx, u32 x, u32 width, GLenum format, GLenum type, Type const *data, u32 alignment = sizeof(Type))
            {
                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,   alignment);
                __gl_DumpError glPixelStorei(GL_UNPACK_SKIP_PIXELS, skipx);

                __gl_DumpError glTexSubImage1D(m_target, level, x, width, format, type, (GLvoid const *)data);

                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,   4);
                __gl_DumpError glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
            }

            template< typename Type >
            void LoadSubImage2D(u32 level, u32 stride, u32 skipx, u32 skipy, u32 x, u32 y, u32 width, u32 height, GLenum format, GLenum type, u8 const *data, u32 alignment = sizeof(Type))
            {
                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,   alignment);
                __gl_DumpError glPixelStorei(GL_UNPACK_ROW_LENGTH,  stride);
                __gl_DumpError glPixelStorei(GL_UNPACK_SKIP_PIXELS, skipx);
                __gl_DumpError glPixelStorei(GL_UNPACK_SKIP_ROWS,   skipy);

                __gl_DumpError glTexSubImage2D(m_target, level, x, y, width, height, format, type, (GLvoid const *)data);

                __gl_DumpError glPixelStorei(GL_UNPACK_ALIGNMENT,   4);
                __gl_DumpError glPixelStorei(GL_UNPACK_ROW_LENGTH,  0);
                __gl_DumpError glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
                __gl_DumpError glPixelStorei(GL_UNPACK_SKIP_ROWS,   0);
            }

            template< typename Type >
            void StoreImage2D(u32 stride, u32 width, u32 height, GLenum format, GLenum type, Type *data, u32 alignment = sizeof(Type))
            {
                __gl_DumpError glPixelStorei(GL_PACK_ALIGNMENT,    alignment);
                __gl_DumpError glPixelStorei(GL_PACK_ROW_LENGTH,   stride);

                __gl_DebugInfo theReadBuffer.Apply();

                __gl_DumpError glReadPixels(0, 0, width, height, (GLvoid *)data);

                __gl_DumpError glPixelStorei(GL_PACK_ALIGNMENT,    4);
                __gl_DumpError glPixelStorei(GL_PACK_ROW_LENGTH,   0);
            }

            template< typename Type >
            void StoreImage2D(u32 stride, GLenum format, GLenum type, Type *data, u32 alignment = sizeof(Type))
            {
                __gl_DumpError glPixelStorei(GL_PACK_ALIGNMENT,    alignment);
                __gl_DumpError glPixelStorei(GL_PACK_ROW_LENGTH,   stride);

                __gl_DumpError glGetTexImage(m_target, 0, format, type, (GLvoid *)data);

                __gl_DumpError glPixelStorei(GL_PACK_ALIGNMENT,    4);
                __gl_DumpError glPixelStorei(GL_PACK_ROW_LENGTH,   0);
            }

            void Enable()
            {
                __gl_DumpError glEnable(m_target);
            }

            void Disable()
            {
                __gl_DumpError glDisable(m_target);
            }


            __forceinline GLuint Id() const             { return m_id; }
            __forceinline GLenum Target() const         { return m_target; }
            __forceinline GLuint Unit() const           { return m_unit; }
            __forceinline GLuint InternalFormat() const { return m_internal_format; }

            __forceinline u32    Stride() const         { return m_stride; }
            __forceinline u32    Width() const          { return m_width; }
            __forceinline u32    Height() const         { return m_height; }

            void LoadImage2D(wchar_t * file, wchar_t * type = L"PNG", HINSTANCE instance = NULL);
            void LoadImage2D(UINT id, wchar_t * type = L"PNG", HINSTANCE instance = NULL);

            using DeletableObject::Id;
            using DeletableObject::Deletable;

        protected:
            GLenum m_target;
            GLuint m_unit;
            GLenum m_internal_format;

            u32    m_stride;
            u32    m_width;
            u32    m_height;
        };

        class SwizzledTexture : protected Texture
        {
            //static char const UNSWIZZLER_FS[] =
            //    "#version 140\n"
            //    "#define BPP %BPP%"
            //    "uniform int log2_w;"
            //    "uniform sampler1D base;"
            //    "float unswizzle(int offset, int log2_w)"
            //    "{"
            //    "   if (log2_w <= 4) return float(offset);"
            //    "   int w_mask = (1 << log2_w) - 1;"
            //    "   ivec2 m = ivec2(offset & 0xf,                   offset & 0x70);"
            //    "   ivec2 b = ivec2(offset & ((w_mask & 0xf) << 7), offset & (~7 << log2_w));"
            //    "   return float(b.y | (b.x >> 3) | (m.y << (log2_w - 4)) | m.x);"
            //    "}"
            //    "void main()"
            //    "{"
            //    "   float index  = unswizzle(int(gl_TexCoord[0].x) + int(gl_TexCoord[0].y) << log2_w, log2_w)/%BPP%;"
            //    "   gl_FragColor = texture1D(base, (index + 0.5) / pow(float(1 << log2_w), 2.0)).rgba;"
            //    "}"
            //    ;
        };

        class DepalettizedTexture : protected Texture
        {
            //static char const DEPALETTIZER_FS[] =
            //    "#version 140\n"
            //    "#define NUM_COLORS %NUM_COLORS%\n"
            //    "uniform sampler2D base;"
            //    "uniform sampler1D clut;"
            //    "void main()"
            //    "{"
            //    "   float sample = texture2D(base, gl_TexCoord[0].xy).r;\n"
            //    "   float index  = floor(sample * float(NUM_COLORS-1));\n"
            //    "   gl_FragColor = texture1D(clut, (index + 0.5) / float(NUM_COLORS)).rgba;\n"
            //    "}"
            //    ;
        };

    }
}
#endif // hal_ogl_Texture_h__
