#include "hal.ogl.Core.h"

namespace emu
{
    namespace log
    {
        SubCategory ogl(hal, "ogl", "Open GL");
    }
}

#define LOAD_FUNC1(f)       f = (hal::ogl::Core::f##FUNC)(__glew##f)
#define LOAD_FUNC2(f, name) f = (hal::ogl::Core::f##FUNC)(name)

hal::ogl::Core gl;

bool hal::ogl::Core::framebuffer_object;
bool hal::ogl::Core::texture_lod_bias;
bool hal::ogl::Core::depth_bounds_test;
bool hal::ogl::Core::sampler_objects;
bool hal::ogl::Core::shader_image_load_store;
bool hal::ogl::Core::texture_integer;
bool hal::ogl::Core::transform_feedback;
bool hal::ogl::Core::program_binary;
bool hal::ogl::Core::version_4_0;

hal::ogl::Core::IsRenderbufferFUNC                      hal::ogl::Core::IsRenderbuffer;
hal::ogl::Core::BindRenderbufferFUNC                    hal::ogl::Core::BindRenderbuffer;
hal::ogl::Core::DeleteRenderbuffersFUNC                 hal::ogl::Core::DeleteRenderbuffers;
hal::ogl::Core::GenRenderbuffersFUNC                    hal::ogl::Core::GenRenderbuffers;
hal::ogl::Core::RenderbufferStorageFUNC                 hal::ogl::Core::RenderbufferStorage;
hal::ogl::Core::RenderbufferStorageMultisampleFUNC      hal::ogl::Core::RenderbufferStorageMultisample;
hal::ogl::Core::GetRenderbufferParameterivFUNC          hal::ogl::Core::GetRenderbufferParameteriv;
hal::ogl::Core::IsFramebufferFUNC                       hal::ogl::Core::IsFramebuffer;
hal::ogl::Core::BindFramebufferFUNC                     hal::ogl::Core::BindFramebuffer;
hal::ogl::Core::DeleteFramebuffersFUNC                  hal::ogl::Core::DeleteFramebuffers;
hal::ogl::Core::GenFramebuffersFUNC                     hal::ogl::Core::GenFramebuffers;
hal::ogl::Core::CheckFramebufferStatusFUNC              hal::ogl::Core::CheckFramebufferStatus;
hal::ogl::Core::FramebufferTexture1DFUNC                hal::ogl::Core::FramebufferTexture1D;
hal::ogl::Core::FramebufferTexture2DFUNC                hal::ogl::Core::FramebufferTexture2D;
hal::ogl::Core::FramebufferTexture3DFUNC                hal::ogl::Core::FramebufferTexture3D;
hal::ogl::Core::FramebufferTextureLayerFUNC             hal::ogl::Core::FramebufferTextureLayer;
hal::ogl::Core::FramebufferRenderbufferFUNC             hal::ogl::Core::FramebufferRenderbuffer;
hal::ogl::Core::GetFramebufferAttachmentParameterivFUNC hal::ogl::Core::GetFramebufferAttachmentParameteriv;
hal::ogl::Core::BlitFramebufferFUNC                     hal::ogl::Core::BlitFramebuffer;
hal::ogl::Core::GenerateMipmapFUNC                      hal::ogl::Core::GenerateMipmap;


__noinline void hal::ogl::Core::init_framebuffer_object()
{
    framebuffer_object = false;
    {
        IsRenderbuffer                      = NULL;
        BindRenderbuffer                    = NULL;
        DeleteRenderbuffers                 = NULL;
        GenRenderbuffers                    = NULL;
        RenderbufferStorage                 = NULL;
        RenderbufferStorageMultisample      = NULL;
        GetRenderbufferParameteriv          = NULL;
        IsFramebuffer                       = NULL;
        BindFramebuffer                     = NULL;
        DeleteFramebuffers                  = NULL;
        GenFramebuffers                     = NULL;
        CheckFramebufferStatus              = NULL;
        FramebufferTexture1D                = NULL;
        FramebufferTexture2D                = NULL;
        FramebufferTexture3D                = NULL;
        FramebufferTextureLayer             = NULL;
        FramebufferRenderbuffer             = NULL;
        GetFramebufferAttachmentParameteriv = NULL;
        BlitFramebuffer                     = NULL;
        GenerateMipmap                      = NULL;
    }

    if (__GLEW_ARB_framebuffer_object)
    {
        framebuffer_object = true;

        LOAD_FUNC1(IsRenderbuffer);
        LOAD_FUNC1(BindRenderbuffer);
        LOAD_FUNC1(DeleteRenderbuffers);
        LOAD_FUNC1(GenRenderbuffers);
        LOAD_FUNC1(RenderbufferStorage);
        LOAD_FUNC1(RenderbufferStorageMultisample);
        LOAD_FUNC1(GetRenderbufferParameteriv);
        LOAD_FUNC1(IsFramebuffer);
        LOAD_FUNC1(BindFramebuffer);
        LOAD_FUNC1(DeleteFramebuffers);
        LOAD_FUNC1(GenFramebuffers);
        LOAD_FUNC1(CheckFramebufferStatus);
        LOAD_FUNC1(FramebufferTexture1D);
        LOAD_FUNC1(FramebufferTexture2D);
        LOAD_FUNC1(FramebufferTexture3D);
        LOAD_FUNC1(FramebufferTextureLayer);
        LOAD_FUNC1(FramebufferRenderbuffer);
        LOAD_FUNC1(GetFramebufferAttachmentParameteriv);
        LOAD_FUNC1(BlitFramebuffer);
        LOAD_FUNC1(GenerateMipmap);
    }
    else
    {
        int extensions = 0;

        if (__GLEW_EXT_framebuffer_object)
        {
            extensions++;

            LOAD_FUNC2(IsRenderbuffer, glIsRenderbufferEXT);
            LOAD_FUNC2(BindRenderbuffer, glBindRenderbufferEXT);
            LOAD_FUNC2(DeleteRenderbuffers, glDeleteRenderbuffersEXT);
            LOAD_FUNC2(GenRenderbuffers, glGenRenderbuffersEXT);
            LOAD_FUNC2(RenderbufferStorage, glRenderbufferStorageEXT);
            LOAD_FUNC2(GetRenderbufferParameteriv, glGetRenderbufferParameterivEXT);
            LOAD_FUNC2(IsFramebuffer, glIsFramebufferEXT);
            LOAD_FUNC2(BindFramebuffer, glBindFramebufferEXT);
            LOAD_FUNC2(DeleteFramebuffers, glDeleteFramebuffersEXT);
            LOAD_FUNC2(GenFramebuffers, glGenFramebuffersEXT);
            LOAD_FUNC2(CheckFramebufferStatus, glCheckFramebufferStatusEXT);
            LOAD_FUNC2(FramebufferTexture1D, glFramebufferTexture1DEXT);
            LOAD_FUNC2(FramebufferTexture2D, glFramebufferTexture2DEXT);
            LOAD_FUNC2(FramebufferTexture3D, glFramebufferTexture3DEXT);
            LOAD_FUNC2(FramebufferRenderbuffer, glFramebufferRenderbufferEXT);
            LOAD_FUNC2(GetFramebufferAttachmentParameteriv, glGetFramebufferAttachmentParameterivEXT);
            LOAD_FUNC2(GenerateMipmap, glGenerateMipmapEXT);
        }
        if (__GLEW_EXT_framebuffer_multisample)
        {
            extensions++;

            LOAD_FUNC2(RenderbufferStorageMultisample, glRenderbufferStorageMultisampleEXT);
        }
        if (__GLEW_ARB_geometry_shader4)
        {
            extensions++;

            LOAD_FUNC2(FramebufferTextureLayer, glFramebufferTextureLayerARB);
        }
        else if (__GLEW_EXT_geometry_shader4)
        {
            extensions++;

            LOAD_FUNC2(FramebufferTextureLayer, glFramebufferTextureLayerEXT);
        }
        if (__GLEW_EXT_framebuffer_blit)
        {
            extensions++;

            LOAD_FUNC2(BlitFramebuffer, glBlitFramebufferEXT);
        }

        framebuffer_object = (extensions == 5);
    }
}

hal::ogl::Core::DepthBoundsFUNC hal::ogl::Core::DepthBounds;

#if 0
static void APIENTRY DepthBoundDEFAULT(GLclampd, GLclampd)
{
    // do nothing :/
}
#endif

__noinline void hal::ogl::Core::init_depth_bounds_test()
{
    depth_bounds_test = false;
    {
        DepthBounds = 0;
    }

    if (__GLEW_EXT_depth_bounds_test)
    {
        depth_bounds_test = true;

        LOAD_FUNC2(DepthBounds, glDepthBoundsEXT);
    }
}

hal::ogl::Core::BindSamplerFUNC                         hal::ogl::Core::BindSampler;
hal::ogl::Core::DeleteSamplersFUNC                      hal::ogl::Core::DeleteSamplers;
hal::ogl::Core::GenSamplersFUNC                         hal::ogl::Core::GenSamplers;
hal::ogl::Core::GetSamplerParameterIivFUNC              hal::ogl::Core::GetSamplerParameterIiv;
hal::ogl::Core::GetSamplerParameterIuivFUNC             hal::ogl::Core::GetSamplerParameterIuiv;
hal::ogl::Core::GetSamplerParameterfvFUNC               hal::ogl::Core::GetSamplerParameterfv;
hal::ogl::Core::GetSamplerParameterivFUNC               hal::ogl::Core::GetSamplerParameteriv;
hal::ogl::Core::IsSamplerFUNC                           hal::ogl::Core::IsSampler;
hal::ogl::Core::SamplerParameterIivFUNC                 hal::ogl::Core::SamplerParameterIiv;
hal::ogl::Core::SamplerParameterIuivFUNC                hal::ogl::Core::SamplerParameterIuiv;
hal::ogl::Core::SamplerParameterfFUNC                   hal::ogl::Core::SamplerParameterf;
hal::ogl::Core::SamplerParameterfvFUNC                  hal::ogl::Core::SamplerParameterfv;
hal::ogl::Core::SamplerParameteriFUNC                   hal::ogl::Core::SamplerParameteri;
hal::ogl::Core::SamplerParameterivFUNC                  hal::ogl::Core::SamplerParameteriv;


__noinline void hal::ogl::Core::init_sampler_objects()
{
    sampler_objects = false;
    {
        BindSampler                         = NULL;
        DeleteSamplers                      = NULL;
        GenSamplers                         = NULL;
        GetSamplerParameterIiv              = NULL;
        GetSamplerParameterIuiv             = NULL;
        GetSamplerParameterfv               = NULL;
        GetSamplerParameteriv               = NULL;
        IsSampler                           = NULL;
        SamplerParameterIiv                 = NULL;
        SamplerParameterIuiv                = NULL;
        SamplerParameterf                   = NULL;
        SamplerParameterfv                  = NULL;
        SamplerParameteri                   = NULL;
        SamplerParameteriv                  = NULL;
    }

    if (__GLEW_ARB_sampler_objects)
    {
        sampler_objects = true;

        LOAD_FUNC1(BindSampler);
        LOAD_FUNC1(DeleteSamplers);
        LOAD_FUNC1(GenSamplers);
        LOAD_FUNC1(GetSamplerParameterIiv);
        LOAD_FUNC1(GetSamplerParameterIuiv);
        LOAD_FUNC1(GetSamplerParameterfv);
        LOAD_FUNC1(GetSamplerParameteriv);
        LOAD_FUNC1(IsSampler);
        LOAD_FUNC1(SamplerParameterIiv);
        LOAD_FUNC1(SamplerParameterIuiv);
        LOAD_FUNC1(SamplerParameterf);
        LOAD_FUNC1(SamplerParameterfv);
        LOAD_FUNC1(SamplerParameteri);
        LOAD_FUNC1(SamplerParameteriv);
    }
}

hal::ogl::Core::BindImageTextureFUNC                    hal::ogl::Core::BindImageTexture;
hal::ogl::Core::MemoryBarrierFUNC                       hal::ogl::Core::MemoryBarrier;

__noinline void hal::ogl::Core::init_shader_image_load_store()
{
    shader_image_load_store = false;
    {
        BindImageTexture                    = NULL;
        MemoryBarrier                       = NULL;
    }

    if (__GLEW_ARB_shader_image_load_store)
    {
        shader_image_load_store = true;

        LOAD_FUNC1(BindImageTexture);
        LOAD_FUNC1(MemoryBarrier);
    }
    else if (__GLEW_EXT_shader_image_load_store)
    {
        shader_image_load_store = true;

        LOAD_FUNC2(BindImageTexture, glBindImageTextureEXT);
        LOAD_FUNC2(MemoryBarrier, glMemoryBarrierEXT);
    }
}

hal::ogl::Core::BindTransformFeedbackFUNC               hal::ogl::Core::BindTransformFeedback;
hal::ogl::Core::DeleteTransformFeedbacksFUNC            hal::ogl::Core::DeleteTransformFeedbacks;
hal::ogl::Core::DrawTransformFeedbackFUNC               hal::ogl::Core::DrawTransformFeedback;
hal::ogl::Core::GenTransformFeedbacksFUNC               hal::ogl::Core::GenTransformFeedbacks;
hal::ogl::Core::IsTransformFeedbackFUNC                 hal::ogl::Core::IsTransformFeedback;
hal::ogl::Core::PauseTransformFeedbackFUNC              hal::ogl::Core::PauseTransformFeedback;
hal::ogl::Core::ResumeTransformFeedbackFUNC             hal::ogl::Core::ResumeTransformFeedback;
hal::ogl::Core::BeginQueryIndexedFUNC                   hal::ogl::Core::BeginQueryIndexed;
hal::ogl::Core::DrawTransformFeedbackStreamFUNC         hal::ogl::Core::DrawTransformFeedbackStream;
hal::ogl::Core::EndQueryIndexedFUNC                     hal::ogl::Core::EndQueryIndexed;
hal::ogl::Core::GetQueryIndexedivFUNC                   hal::ogl::Core::GetQueryIndexediv;

__noinline void hal::ogl::Core::init_transform_feedback()
{
    transform_feedback = false;
    {
        BindTransformFeedback               = NULL;
        DeleteTransformFeedbacks            = NULL;
        DrawTransformFeedback               = NULL;
        GenTransformFeedbacks               = NULL;
        IsTransformFeedback                 = NULL;
        PauseTransformFeedback              = NULL;
        ResumeTransformFeedback             = NULL;
        BeginQueryIndexed                   = NULL;
        DrawTransformFeedbackStream         = NULL;
        EndQueryIndexed                     = NULL;
        GetQueryIndexediv                   = NULL;
    }

    if (__GLEW_ARB_transform_feedback2)
    {
        LOAD_FUNC1(BindTransformFeedback);
        LOAD_FUNC1(DeleteTransformFeedbacks);
        LOAD_FUNC1(DrawTransformFeedback);
        LOAD_FUNC1(GenTransformFeedbacks);
        LOAD_FUNC1(IsTransformFeedback);
        LOAD_FUNC1(PauseTransformFeedback);
        LOAD_FUNC1(ResumeTransformFeedback);

        if (__GLEW_ARB_transform_feedback3)
        {
            transform_feedback = true;

            LOAD_FUNC1(BeginQueryIndexed);
            LOAD_FUNC1(DrawTransformFeedbackStream);
            LOAD_FUNC1(EndQueryIndexed);
            LOAD_FUNC1(GetQueryIndexediv);
        }
    }
}

hal::ogl::Core::ClearColorIiFUNC                        hal::ogl::Core::ClearColorIi;
hal::ogl::Core::ClearColorIuiFUNC                       hal::ogl::Core::ClearColorIui;


__noinline void hal::ogl::Core::init_texture_integer()
{
    texture_integer = false;
    {
        ClearColorIi                        = NULL;
        ClearColorIui                       = NULL;
    }

    if (__GLEW_EXT_texture_integer)
    {
        texture_integer = true;

        LOAD_FUNC2(ClearColorIi,        glClearColorIiEXT);
        LOAD_FUNC2(ClearColorIui,       glClearColorIuiEXT);
    }
}

hal::ogl::Core::GetProgramBinaryFUNC                    hal::ogl::Core::GetProgramBinary;
hal::ogl::Core::ProgramBinaryFUNC                       hal::ogl::Core::ProgramBinary;
hal::ogl::Core::ProgramParameteriFUNC                   hal::ogl::Core::ProgramParameteri;

__noinline void hal::ogl::Core::init_program_binary()
{
    program_binary = false;
    {
        GetProgramBinary                    = NULL;
        ProgramBinary                       = NULL;
        ProgramParameteri                   = NULL;
    }

    if (__GLEW_ARB_get_program_binary)
    {
        program_binary = true;

        LOAD_FUNC1(GetProgramBinary);
        LOAD_FUNC1(ProgramBinary);
        LOAD_FUNC1(ProgramParameteri);
    }
}


__noinline bool hal::ogl::Core::Initialize()
{
    glewExperimental = GL_TRUE;
    glewInit();

    version_4_0 = __GLEW_VERSION_4_0 != 0;

    init_framebuffer_object();
    init_depth_bounds_test();
    init_sampler_objects();
#ifdef OPENGL420_NEEDED
    init_shader_image_load_store();
    init_transform_feedback();
#endif
    init_texture_integer();
    init_program_binary();

    //if (!version_4_0 || !framebuffer_object || !sampler_objects || !shader_image_load_store || !transform_feedback || !program_binary)
    //{
    //    return false;
    //}

    // DrawRectangleArrays
    for (int i = 0, p = 0; i < 65536/4; ++i, p += 4)
    {
        rectangle_arrays_i[i] = p;
        rectangle_arrays_c[i] = 4;
    }

    return true;
}

__noinline void hal::ogl::Core::Terminate()
{

}

hal::ogl::Core::DebugInfo * hal::ogl::Core::__this_debuginfo__ = 0;


bool hal::ogl::Core::CheckError()
{
    int error;
    if ((error = glGetError()) != GL_NO_ERROR)
    {
        char const * error_string;
        switch (error)
        {
        case GL_INVALID_ENUM:
            error_string = "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error_string = "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            error_string = "GL_INVALID_OPERATION";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error_string = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            error_string = "GL_OUT_OF_MEMORY";
            break;
        default:
            error_string = "UNKNOWN";
            break;
        }
        errorf(ogl, "Error(%s)", error_string);
    }
    return error == GL_NO_ERROR;
}

//void gl_Core::callThroughTrampoline(void* function)
//{
//    u32 *address = (u32 *)(((u8 *)__returnaddress()) - 4);
//
//    DWORD oldprot, dummy;
//
//    ::VirtualProtect((void *)address, 4, PAGE_EXECUTE_READWRITE, &oldprot);
//
//    *address = u32(function) - u32(address) - 4;
//
//    ::VirtualProtect((void *)address, 4, oldprot, &dummy);
//
//    *((u32 *)__returnaddressptr()) -= 5; // let gl_Core::callThroughTrampoline returns to the instruction which calls it first so 'function' can be called then
//}

GLint   hal::ogl::Core::rectangle_arrays_i[65536/4];
GLsizei hal::ogl::Core::rectangle_arrays_c[65536/4];
