#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "userenv.lib")
#pragma comment(lib, "ntdll.lib")

#include "gl\glew.h"
#include "gl\wglew.h"

#include "emu.log.h"
#include "lle.mmu.h"
#include "hal.os.h"
#include "hal.os.Clock.h"
#include "hal.video.h"
#include "hal.ogl.Core.h"
#include "hal.ogl.Texture.h"
#include "hal.ogl.UnifiedProgram.h"
#include "hal.ogl.VertexArrayObject.h"
#include "hal.ogl.VertexBufferObject.h"
#include "hal.npa.h"

static hal::npa::Event npa_update_display_event("Update Display Buffer");
static hal::npa::Event npa_render_display_event("Render Display Buffer");
static hal::npa::Event npa_present_display_event("Present Display Buffer");

namespace hal
{
    namespace video
    {
        struct Implementation : Interface
		{
			Implementation()
			:	m_hDC(0)
			,	m_hRC(0)
            ,   m_toggle_vsync(0)
			,   m_display_fb_texture(&m_nodisplay_texture)
			,   m_display_fb_previous_start(0)
			,   m_display_fb_previous_stride(0)
			,   m_display_width(0)
			,   m_display_height(0)
			,   m_display_orientation(0)
			,   m_display_filter(0)
			,   m_display_clear(2)
            {
            }

            ~Implementation()
            {
            }

			bool DllProcessAttach()
			{
				long version = Implementation::version;

				forcef(emu, "pspe4all-hal.video(version=%d.%02d)", (version>>8)&255, version&255);
				infof( emu, "pspe4all-hal.video: Loaded");

				bool result = true;

				return result ? TRUE : FALSE;
			}

			void DllProcessDetach()
			{
				infof(emu, "pspe4all-hal.video: Unloaded");
			}

            //////////////////////////////////////////////////////////////////////////

            GLvoid glPrintf(char const * fmt, ...)
            {
                if (!fmt) return;

                char text[256];
                va_list ap;
                va_start(ap, fmt);
                vsprintf(text, fmt, ap);
                va_end(ap);

                glPushAttrib(GL_LIST_BIT);
                glListBase(m_fontbase - 32);
                glCallLists((GLsizei)strlen(text), GL_UNSIGNED_BYTE, text);
                glPopAttrib();
            }

            //////////////////////////////////////////////////////////////////////////

			bool CreateDisplay(HDC hDC)
			{
				/// this sequence should be done in a thread dedicated to Open GL rendering

				m_hDC = hDC;

				// Are we able to get a rendering context?
				if (!(m_hRC = wglCreateContext(m_hDC)))
				{
					return false;
				}

				// Try to activate the rendering context
				if (!wglMakeCurrent(m_hDC, m_hRC))	
				{
					return false;
				}

                static bool first = false;

                if (!first)
                {
                    hal::ogl::Core().Initialize();

                    wglSwapIntervalEXT(-1);
                }

                HFONT font, oldfont;

                m_fontbase = glGenLists(96);

                font = ::CreateFontA(-16, 0, 0, 0, FALSE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                                     FF_DONTCARE|FIXED_PITCH, "Arial");

                oldfont = (HFONT)SelectObject(hDC, font);
                wglUseFontBitmaps(hDC, 32, 96, m_fontbase);
                ::SelectObject(hDC, oldfont);
                ::DeleteObject(font);

                m_fps_prior = m_fps_clock.Get();
                m_vid_prior = m_fps_prior;

				return true;
			}

			bool ReleaseDisplay()
			{
				/// this sequence should be done in a thread dedicated to Open GL rendering

				__gl_DebugInfo m_nodisplay_texture .Delete();
				__gl_DebugInfo m_display_texture   .Delete();
				__gl_DebugInfo m_display_fb_program.Delete();
				__gl_DebugInfo m_display_fb_vbo    .Delete();
				__gl_DebugInfo m_display_fb_vao    .Delete();

                glDeleteLists(m_fontbase, 96);

				bool result = true;
				if (m_hRC)
				{
					if (!wglMakeCurrent(NULL,NULL))
					{
						result = false;
					}

					if (!wglDeleteContext(m_hRC))
					{
						result = false;
					}
				}

				return result;
			}

			bool PrepareDisplay()
			{
				/// this sequence should be done in a thread dedicated to Open GL rendering
				static GLclampf black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

				__gl_DebugInfo m_display_fb_vao    .Create();
				__gl_DebugInfo m_display_fb_vbo    .Create();
				__gl_DebugInfo m_display_fb_program.Create();
				__gl_DebugInfo m_nodisplay_texture .Create();
				__gl_DebugInfo m_display_texture   .Create();

				__gl_DumpError glShadeModel(GL_SMOOTH);
				__gl_DumpError glClearColor(black[0], black[1], black[2], black[3]);
				__gl_DumpError glClearDepth(1.0f);
				__gl_DumpError glDisable(GL_DEPTH_TEST);
				__gl_DumpError glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				__gl_DumpError glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

				__gl_DebugInfo m_nodisplay_texture.Active(7);
				__gl_DebugInfo m_nodisplay_texture.SetInternalFormat(GL_RGBA);
				__gl_DebugInfo m_nodisplay_texture.Bind(GL_TEXTURE_RECTANGLE);
				__gl_DebugInfo m_nodisplay_texture.LoadImage2D(101, L"PNG", ::GetModuleHandleW(__ConfigurationDllStringW(L"pspe4all-emu")));
				__gl_DebugInfo m_nodisplay_texture.Unbind();

				m_display_orientation = 0;
				m_display_filter      = 1;

				///----------------------------------------------------------

				static GLfloat vbo_data[4*4*4] =
				{
					// 0°
					-1.0f, -1.0f, 0.0f, 0.0f,
					+1.0f, -1.0f, 1.0f, 0.0f,
					+1.0f, +1.0f, 1.0f, 1.0f,
					-1.0f, +1.0f, 0.0f, 1.0f,
					// 90°
					-1.0f, -1.0f, 1.0f, 0.0f,
					+1.0f, -1.0f, 1.0f, 1.0f,
					+1.0f, +1.0f, 0.0f, 1.0f,
					-1.0f, +1.0f, 0.0f, 0.0f,
					// 180°
					-1.0f, -1.0f, 1.0f, 1.0f,
					+1.0f, -1.0f, 0.0f, 1.0f,
					+1.0f, +1.0f, 0.0f, 0.0f,
					-1.0f, +1.0f, 1.0f, 0.0f,
					// 270°
					-1.0f, -1.0f, 0.0f, 1.0f,
					+1.0f, -1.0f, 0.0f, 0.0f,
					+1.0f, +1.0f, 1.0f, 0.0f,
					-1.0f, +1.0f, 1.0f, 1.0f
				};

				__gl_DebugInfo m_display_fb_vao.Bind();
				{
					__gl_DebugInfo m_display_fb_vbo.Bind(vbo_data, sizeof(vbo_data));
					__gl_DebugInfo m_display_fb_vbo.SetVertexPointer(4, GL_FLOAT, sizeof(f32)*4, 0);
				}
				__gl_DebugInfo m_display_fb_vao.Unbind();

				__gl_DebugInfo m_display_fb_program.CompileVertex(m_vertex_shader_source);
				__gl_DebugInfo m_display_fb_program.CompileFragment(m_fragment_shader_source);
				__gl_DebugInfo m_display_fb_program.Link();

				__gl_DebugInfo m_display_uniform_ortho                = m_display_fb_program.GetUniformLocation("ortho");
				__gl_DebugInfo m_display_uniform_scale                = m_display_fb_program.GetUniformLocation("scale");
				__gl_DebugInfo m_display_uniform_size                 = m_display_fb_program.GetUniformLocation("size");
				__gl_DebugInfo m_display_uniform_offset               = m_display_fb_program.GetUniformLocation("offset");

				__gl_DebugInfo m_display_uniform_textureNearest       = m_display_fb_program.GetSubroutineIndex(GL_FRAGMENT_SHADER, "textureNearest");
				__gl_DebugInfo m_display_uniform_textureBilinear      = m_display_fb_program.GetSubroutineIndex(GL_FRAGMENT_SHADER, "textureBilinear");
				__gl_DebugInfo m_display_uniform_textureHQ2X          = m_display_fb_program.GetSubroutineIndex(GL_FRAGMENT_SHADER, "textureHQ2X");

				__gl_DebugInfo m_display_uniform_textureCoordNearest  = m_display_fb_program.GetSubroutineIndex(GL_VERTEX_SHADER, "textureCoordNearest");
				__gl_DebugInfo m_display_uniform_textureCoordBilinear = m_display_fb_program.GetSubroutineIndex(GL_VERTEX_SHADER, "textureCoordBilinear");
				__gl_DebugInfo m_display_uniform_textureCoordHQ2X     = m_display_fb_program.GetSubroutineIndex(GL_VERTEX_SHADER, "textureCoordHQ2X");

				__gl_DumpError glMatrixMode(GL_TEXTURE);
				__gl_DumpError glLoadIdentity();

				__gl_DumpError glMatrixMode(GL_MODELVIEW);
				__gl_DumpError glLoadIdentity();

				__gl_DumpError glMatrixMode(GL_PROJECTION);
				__gl_DumpError glLoadIdentity();

				return true;
			}

			void ResizeDisplay(int width, int height)
			{
				if (height == 0)
				{
					height = 1;
				}

				m_window_width  = width;
				m_window_height = height;
			}

			bool UpdateDisplay()
			{
                f64 vid_time = m_fps_clock.Get();
                __npa_Event(npa_update_display_event)
                {
                    if (address)
                    {
                        m_display_fb_texture = &m_display_texture;

                        __gl_DebugInfo m_display_fb_texture->Active(7);
                        __gl_DebugInfo m_display_fb_texture->Bind(GL_TEXTURE_RECTANGLE);

                        switch (format & 3)
                        {
                        case 0: __gl_DebugInfo m_display_fb_texture->LoadImage2D(stride, width, height, GL_RGB,  GL_UNSIGNED_SHORT_5_6_5_REV,   lle::mmu::Addr< u16 >(address)); break;
                        case 1: __gl_DebugInfo m_display_fb_texture->LoadImage2D(stride, width, height, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, lle::mmu::Addr< u16 >(address)); break;
                        case 2: __gl_DebugInfo m_display_fb_texture->LoadImage2D(stride, width, height, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4_REV, lle::mmu::Addr< u16 >(address)); break;
                        case 3: __gl_DebugInfo m_display_fb_texture->LoadImage2D(stride, width, height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV,   lle::mmu::Addr< u32 >(address)); break;
                        }

                        __gl_DebugInfo m_display_fb_texture->Unbind();
                    }
                    else
                    {
                        m_display_fb_texture = &m_nodisplay_texture;
                    }
                }
                m_vid_delta += m_fps_clock.Get() - vid_time;

				return true;
			}

			__noinline bool RenderDisplay()
			{
                f64 vid_time = m_fps_clock.Get();

                __npa_Event(npa_render_display_event)
                {
                    __gl_DumpError glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    // Place your code here!
                    f32 lcd_width  = f32(m_window_width);
                    f32 lcd_height = f32(m_window_height);
                    f32 tex_width  = f32(m_display_fb_texture->Width());
                    f32 tex_height = f32(m_display_fb_texture->Height());

                    __gl_DumpError glViewport(0, 0, m_window_width, m_window_height);
                    __gl_DumpError glScissor (0, 0, m_window_width, m_window_height);
                    __gl_DumpError glEnable(GL_SCISSOR_TEST);

                    ogl::UnifiedProgram & program = m_display_fb_program;

                    __gl_DebugInfo program.Bind();

                    __gl_DebugInfo m_display_fb_texture->Active(7);
                    __gl_DebugInfo m_display_fb_texture->Bind(GL_TEXTURE_RECTANGLE);
                    __gl_DebugInfo m_display_fb_texture->Enable();

                    __gl_DumpError glUniform2f(m_display_uniform_size, tex_width, tex_height);
                    __gl_DumpError glUniform2f(m_display_uniform_offset, 0.0f, 0.0f);

                    switch (m_display_filter)
                    {
                    case 1:
                        __gl_DebugInfo program.UniformSubroutines(GL_VERTEX_SHADER,   1, &m_display_uniform_textureCoordBilinear);
                        __gl_DebugInfo program.UniformSubroutines(GL_FRAGMENT_SHADER, 1, &m_display_uniform_textureBilinear);
                        break;
                    case 2:
                        __gl_DebugInfo program.UniformSubroutines(GL_VERTEX_SHADER,   1, &m_display_uniform_textureCoordHQ2X);
                        __gl_DebugInfo program.UniformSubroutines(GL_FRAGMENT_SHADER, 1, &m_display_uniform_textureHQ2X);
                        break;
                    default:
                        __gl_DebugInfo program.UniformSubroutines(GL_VERTEX_SHADER,   1, &m_display_uniform_textureCoordNearest);
                        __gl_DebugInfo program.UniformSubroutines(GL_FRAGMENT_SHADER, 1, &m_display_uniform_textureNearest);
                        break;
                    }

                    if (m_display_orientation & 1)
                    {
                        __gl_DumpError glUniform2f(m_display_uniform_scale, tex_height/tex_width,  1.f);
                        __gl_DumpError glUniform2f(m_display_uniform_ortho, lcd_width/lcd_height, -1.f);
                    }
                    else
                    {
                        __gl_DumpError glUniform2f(m_display_uniform_scale, 1.f,  tex_height/tex_width);
                        __gl_DumpError glUniform2f(m_display_uniform_ortho, 1.f, -lcd_height/lcd_width);
                    }

                    __gl_DebugInfo m_display_fb_vao.Bind();

                    __gl_DumpError glDrawArrays(GL_QUADS, 4*(m_display_orientation & 3), 4);

                    __gl_DebugInfo m_display_fb_vao.Unbind();

                    __gl_DebugInfo m_display_fb_texture->Disable();
                    __gl_DebugInfo m_display_fb_texture->Unbind();

                    __gl_DebugInfo program.Unbind();
                }

                static double freq_us  = double(hal::os::Clock::GetElpasedTimeStampPerMicrosecond());
                static double freq_Ghz = freq_us/1000.;

                glColor3f(0.f, 0.8f, 0.2f);
                glRasterPos2f(-1.f, -1.f);

                glPrintf("FPS:%-5d / dTime:%-6.1f ms / VID:%-6.1f ms / CPU:%2.3f Ghz", m_fps_count, m_fps_delta/1000., m_vid_prior/1000., freq_Ghz);

                m_vid_prior = m_vid_delta + m_fps_clock.Get() - vid_time;
                m_vid_delta = 0;

				return true;
			}

			bool PresentDisplay()
			{
                __npa_Event(npa_present_display_event)
                {
                    f64 vid_time = m_fps_clock.Get();

                    ::SwapBuffers(m_hDC);

                    f64 fps_time = m_fps_clock.Get();
                    m_fps_delta  = fps_time - m_fps_prior;
                    m_fps_prior  = fps_time;
                    m_fps_count  = u64(1000000./m_fps_delta);

                    int value = wglGetSwapIntervalEXT();
                    if (!value)
                    {
                        __gl_DumpError glFinish(); // sheesh... I need to do so I can emulate a VSYNC wait in "case CCpu::DoSceDisplayWaitVblankStart:"
                    }

                    if (0 != m_toggle_vsync.Exchange(0))
                    {
                        int value = wglGetSwapIntervalEXT();
                        wglSwapIntervalEXT(!value ? -1 : 0);
                    }

                    m_vid_delta += m_fps_clock.Get() - vid_time;
                }

				return true;
			}

            void ToggleVsync()
            {
                m_toggle_vsync = 1;
            }

        protected:
			HDC                       m_hDC;
			HGLRC					  m_hRC;
            hal::Atomic< int >        m_toggle_vsync;

			ogl::Texture            * m_display_fb_texture;
			ogl::VertexBufferObject   m_display_fb_vbo;
			ogl::VertexArrayObject    m_display_fb_vao;

			u32                       m_display_fb_previous_start;
			u32                       m_display_fb_previous_stride;

			ogl::Texture              m_nodisplay_texture;
			ogl::Texture              m_display_texture;

			u32                       m_window_width;
			u32                       m_window_height;

			u32                       m_display_width;
			u32                       m_display_height;

			u32                       m_display_orientation;
			u32                       m_display_filter;

			u32                       m_display_clear;

			ogl::UnifiedProgram       m_display_fb_program;

			GLint                     m_display_uniform_sampler;
			GLint                     m_display_uniform_offset;
			GLint                     m_display_uniform_size;
			GLint                     m_display_uniform_scale;
			GLint                     m_display_uniform_ortho;

			GLuint                    m_display_uniform_textureNearest;
			GLuint                    m_display_uniform_textureBilinear;
			GLuint                    m_display_uniform_textureHQ2X;

			GLuint                    m_display_uniform_textureCoordNearest;
			GLuint                    m_display_uniform_textureCoordBilinear;
			GLuint                    m_display_uniform_textureCoordHQ2X;

            GLuint                    m_fontbase;

            hal::os::Clock            m_fps_clock;
            f64                       m_fps_prior;
            f64                       m_fps_delta;
            u64                       m_fps_count;
            f64                       m_vid_prior;
            f64                       m_vid_delta;

			static char const         m_vertex_shader_source[];
			static char const         m_fragment_shader_source[];

		private:
			static hal::os::CriticalSection critical_section;
		};

        hal::os::CriticalSection Implementation::critical_section;

		char const Implementation::m_vertex_shader_source[] =
		{
			"#version 420 core" "\n"
			"in vec4 gl_Vertex;"
			"out gl_PerVertex { vec4 gl_Position; };"
			"out vec4 Tv[5];"
			"uniform int orientation;"
			"uniform vec2 ortho;"
			"uniform vec2 scale;"
			"uniform vec2 size;"
			"uniform vec2 offset;"
			"subroutine void TextureCoord();"
			"subroutine uniform TextureCoord textureCoord;"
			"subroutine(TextureCoord) void textureCoordNearest()"
			"{"
			"	Tv[0] = vec4(offset,0.0,0.0)+vec4(gl_Vertex.zw*size,1.0,1.0);"
			"}"
			"subroutine(TextureCoord) void textureCoordBilinear()"
			"{"
			"	Tv[0] = vec4(offset,0.0,0.0)+vec4(gl_Vertex.zw*size,1.0,1.0);"
			"}"
			"subroutine(TextureCoord) void textureCoordHQ2X()"
			"{"
			"	vec2 dg1 = vec2(+0.5,+0.5);"
			"	vec2 dg2 = vec2(-0.5,+0.5);"
			"	vec2 dx  = vec2(+0.5,+0.0);"
			"	vec2 dy  = vec2(+0.0,+0.5);"
			"	Tv[0]    = vec4(offset,0.0,0.0)+vec4(gl_Vertex.zw*size,1.0,1.0);"
			"	Tv[1].xy = Tv[0].xy - dg1;" // c00
			"	Tv[1].zw = Tv[0].xy - dy;"  // c01
			"	Tv[2].xy = Tv[0].xy - dg2;" // c02
			"	Tv[2].zw = Tv[0].xy + dx;"  // c10
			"	Tv[3].xy = Tv[0].xy + dg1;" // c12
			"	Tv[3].zw = Tv[0].xy + dy;"  // c20
			"	Tv[4].xy = Tv[0].xy + dg2;" // c21
			"	Tv[4].zw = Tv[0].xy - dx;"  // c22
			"}"
			"void main()"
			"{"
			"	vec2 P = gl_Vertex.xy*scale;"
			"	gl_Position = vec4(P/ortho,0.0,1.0);"
			"	textureCoord();"
			"}"
		};
		
		char const Implementation::m_fragment_shader_source[] =
		{
			"#version 420 core" "\n"
			"in vec4 Tv[5];"
			"subroutine vec4 TextureFilter();"
			"subroutine uniform TextureFilter textureFilter;"
			"layout(binding = 7) uniform sampler2DRect DB;"
			"subroutine(TextureFilter) vec4 textureNearest()"
			"{"
			"	return texelFetch(DB, ivec2(Tv[0].xy));"
			"}"
			"subroutine(TextureFilter) vec4 textureBilinear()"
			"{"
			"	vec2 texelcoord = Tv[0].xy - 0.5;"
			"	ivec2 index = ivec2(texelcoord);"
			"	ivec2 texelcoords[] = ivec2[4](index + ivec2(0, 0), index + ivec2(1, 0), index + ivec2(1, 1), index + ivec2(0, 1));"
			"	vec4 texel00 = texelFetch(DB, texelcoords[0]);"
			"	vec4 texel10 = texelFetch(DB, texelcoords[1]);"
			"	vec4 texel11 = texelFetch(DB, texelcoords[2]);"
			"	vec4 texel01 = texelFetch(DB, texelcoords[3]);"
			"	vec2 interpolant = fract(texelcoord);"
			"	vec4 texel0 = mix(texel00, texel01, interpolant.y);"
			"	vec4 texel1 = mix(texel10, texel11, interpolant.y);"
			"	return mix(texel0, texel1, interpolant.x);"
			"}"
			"const vec4 max_w = vec4(+0.25);"
			"const vec4 min_w = vec4(-0.05);"
			"subroutine(TextureFilter) vec4 textureHQ2X()"
			"{"
			"	vec3  c00 = texelFetch(DB, ivec2(Tv[1].xy)).rgb;" 
			"	vec3  c10 = texelFetch(DB, ivec2(Tv[1].zw)).rgb;" 
			"	vec3  c20 = texelFetch(DB, ivec2(Tv[2].xy)).rgb;"
			"	vec3  c01 = texelFetch(DB, ivec2(Tv[4].zw)).rgb;" 
			"	vec4  c11 = texelFetch(DB, ivec2(Tv[0].xy)).rgba;"
			"	vec3  c21 = texelFetch(DB, ivec2(Tv[2].zw)).rgb;"
			"	vec3  c02 = texelFetch(DB, ivec2(Tv[4].xy)).rgb;"
			"	vec3  c12 = texelFetch(DB, ivec2(Tv[3].zw)).rgb;"
			"	vec3  c22 = texelFetch(DB, ivec2(Tv[3].xy)).rgb;"
			"	vec3  dt  = vec3(1.0);"
			"	vec2  md  = vec2(dot(abs(c00 - c22), dt), dot(abs(c02 - c20), dt));"
			"	vec4  w   = vec4(dot(abs(c22 - c11.rgb), dt), dot(abs(c02 - c11.rgb), dt), dot(abs(c00 - c11.rgb), dt), dot(abs(c20 - c11.rgb), dt)) * vec4(md.yx, md.yx);"
			"	vec2  t   = w.xz + w.yw;"
			"	float ww  = max(t.x, t.y) + 0.0001;"
			"	c11.rgb   = (w.x * c00 + w.y * c20 + w.z * c22 + w.w * c02 + ww * c11.rgb) / (t.x + t.y + ww);"
			"	vec2  lc  = vec2(-0.25) / (0.12 * vec2(dot(c10 + c12 + c11.rgb, dt), dot(c01 + c21 + c11.rgb, dt)) + vec2(0.25));"
			"	w         = clamp(vec4(lc.xy * vec2(dot(abs(c11.rgb - c10), dt), dot(abs(c11.rgb - c21), dt)), lc.xy * vec2(dot(abs(c11.rgb - c12), dt), dot(abs(c11.rgb - c01), dt))) + vec4(0.325), min_w, max_w);"
			"	return vec4(w.x * c10 + w.y * c21 + w.z * c12 + w.w * c01 + (1.0 - w.x - w.y - w.z - w.w) * c11.rgb, c11.a);"
			"}"
			"void main()"
			"{"
			"	gl_FragColor = textureFilter().rgba;"
			"}"
		};
    }
}

static hal::video::Implementation implementation;

extern "C" __declspec(dllexport) hal::video::Interface * hal_video$GetInterface(long version)
{
    long version_major = (version >> 8) & 255;
    long version_minor = (version >> 0) & 255;

    if (version_major == hal::video::Implementation::version_major && version_minor <= hal::video::Implementation::version_minor)
    {
        return &implementation; 
    }

    char tmp[256];
    sprintf(tmp, "This program requires pspe4all-hal.video.OpengGL4.dll version to be in range [%d.%02d, %d.00[.", hal::video::Implementation::version_major, hal::video::Implementation::version_minor, hal::video::Implementation::version_major+1);
    ::MessageBoxA(NULL, tmp, "PSPE4ALL-HAL", MB_OK | MB_ICONHAND);

    return 0;
}

extern "C" __declspec(dllexport) long GetImplementationVersion()
{
    return hal::video::Implementation::version;
}

extern "C" BOOL WINAPI DllMain(HINSTANCE /*hinstDLL*/, DWORD fdwReason, LPVOID /*lpvReserved*/)
{
    // see this link for best practice with DllMain : http://msdn.microsoft.com/en-us/windows/hardware/gg487379.aspx
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        {
			if (!implementation.DllProcessAttach())
			{
				return FALSE;
			}

            break;
        }
    case DLL_THREAD_ATTACH:
        {
            break;
        }
    case DLL_THREAD_DETACH:
        {
            break;
        }
    case DLL_PROCESS_DETACH:
        {
            __DbgCheckLastError("LastErrorCode test using GetProcessId(NULL)", GetProcessId(NULL));

			implementation.DllProcessDetach();

            break;
        }
    }

    return TRUE;
}

#include "Remotery.c"
