#include "GLFunctions.h"

#ifdef OS_WINDOWS

#define glGetProcAddress wglGetProcAddress
#define GL_GET_PROC_ADR(proc_type, proc_name) g_##proc_name = (proc_type) glGetProcAddress(#proc_name)

#elif defined(VERO4K) || defined(ODROID) || defined(VC)

#define GL_GET_PROC_ADR(proc_type, proc_name) g_##proc_name = (proc_type) dlsym(gles2so, #proc_name);

#elif defined(EGL)

#include <EGL/egl.h>
#include <EGL/eglext.h>
#define glGetProcAddress eglGetProcAddress
#define GL_GET_PROC_ADR(proc_type, proc_name) g_##proc_name = (proc_type) glGetProcAddress(#proc_name)

#elif defined(OS_LINUX)

#include <X11/Xutil.h>
typedef XID GLXContextID;
typedef XID GLXPixmap;
typedef XID GLXDrawable;
typedef XID GLXPbuffer;
typedef XID GLXWindow;
typedef XID GLXFBConfigID;
typedef struct __GLXcontextRec *GLXContext;
typedef struct __GLXFBConfigRec *GLXFBConfig;
#define GLX_GLXEXT_PROTOTYPES
#include <GL/glxext.h>
#define glGetProcAddress glXGetProcAddress
#define GL_GET_PROC_ADR(proc_type, proc_name) g_##proc_name = (proc_type) glGetProcAddress((const GLubyte*)#proc_name)

#elif defined(OS_MAC_OS_X)
#include <dlfcn.h>

static void* AppleGLGetProcAddress (const char *name)
{
	static void* image = NULL;
	if (NULL == image)
		image = dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_LAZY);

	return (image ? dlsym(image, name) : NULL);
}
#define glGetProcAddress AppleGLGetProcAddress
#define GL_GET_PROC_ADR(proc_type, proc_name) g_##proc_name = (proc_type) glGetProcAddress(#proc_name)

#elif defined(OS_IOS)
#include <dlfcn.h>

static void* IOSGLGetProcAddress (const char *name)
{
    return dlsym(RTLD_DEFAULT, name);
}

#define glGetProcAddress IOSGLGetProcAddress
#define GL_GET_PROC_ADR(proc_type, proc_name) g_##proc_name = (proc_type)glGetProcAddress(#proc_name)

#endif

PFNGLENABLEIPROC g_glEnablei;
PFNGLDISABLEIPROC g_glDisablei;
PFNGLGETSTRINGPROC g_glGetString;
PFNGLTEXPARAMETERFPROC g_glTexParameterf;
PFNGLGETFLOATVPROC g_glGetFloatv;
PFNGLVERTEXATTRIB1FPROC g_glVertexAttrib1f;
PFNGLTEXPARAMETERIPROC g_glTexParameteri;
PFNGLBINDRENDERBUFFERPROC g_glBindRenderbuffer;
PFNGLBINDBUFFERPROC g_glBindBuffer;
PFNGLBUFFERSTORAGEPROC g_glBufferStorage;
PFNGLCREATEFRAMEBUFFERSPROC g_glCreateFramebuffers;
PFNGLGETPROGRAMBINARYPROC g_glGetProgramBinary;
PFNGLPROGRAMBINARYPROC g_glProgramBinary;
PFNGLPROGRAMPARAMETERIPROC g_glProgramParameteri;
PFNGLTEXIMAGE2DPROC g_glTexImage2D;
PFNGLNAMEDFRAMEBUFFERTEXTUREPROC g_glNamedFramebufferTexture;
PFNGLTEXTURESUBIMAGE2DPROC g_glTextureSubImage2D;
PFNGLTEXTURESTORAGE2DPROC g_glTextureStorage2D;
PFNGLTEXTUREPARAMETERFPROC g_glTextureParameterf;
PFNGLTEXTUREBARRIERPROC g_glTextureBarrier;
PFNGLTEXTUREBARRIERNVPROC g_glTextureBarrierNV;
PFNGLFINISHPROC g_glFinish;
PFNGLTEXTUREPARAMETERIPROC g_glTextureParameteri;
PFNGLCREATETEXTURESPROC g_glCreateTextures;
PFNGLGETINTEGERVPROC g_glGetIntegerv;
PFNGLREADPIXELSPROC g_glReadPixels;
PFNGLBINDFRAMEBUFFERPROC g_glBindFramebuffer;

void initGLFunctions()
{
    GL_GET_PROC_ADR(PFNGLENABLEIPROC, glEnablei);
    GL_GET_PROC_ADR(PFNGLDISABLEIPROC, glDisablei);
    GL_GET_PROC_ADR(PFNGLGETSTRINGPROC, glGetString);
    GL_GET_PROC_ADR(PFNGLTEXPARAMETERFPROC, glTexParameterf);
    GL_GET_PROC_ADR(PFNGLGETFLOATVPROC, glGetFloatv);
    GL_GET_PROC_ADR(PFNGLVERTEXATTRIB1FPROC, glVertexAttrib1f);
    GL_GET_PROC_ADR(PFNGLTEXPARAMETERIPROC, glTexParameteri);
    GL_GET_PROC_ADR(PFNGLCREATEFRAMEBUFFERSPROC, glCreateFramebuffers);
    GL_GET_PROC_ADR(PFNGLTEXIMAGE2DPROC, glTexImage2D);
    GL_GET_PROC_ADR(PFNGLNAMEDFRAMEBUFFERTEXTUREPROC, glNamedFramebufferTexture);
    GL_GET_PROC_ADR(PFNGLTEXTURESUBIMAGE2DPROC, glTextureSubImage2D);
    GL_GET_PROC_ADR(PFNGLTEXTURESTORAGE2DPROC, glTextureStorage2D);
    GL_GET_PROC_ADR(PFNGLTEXTUREPARAMETERFPROC, glTextureParameterf);
    GL_GET_PROC_ADR(PFNGLTEXTUREBARRIERPROC, glTextureBarrier);
    GL_GET_PROC_ADR(PFNGLTEXTUREBARRIERNVPROC, glTextureBarrierNV);
    GL_GET_PROC_ADR(PFNGLFINISHPROC, glFinish);
    GL_GET_PROC_ADR(PFNGLTEXTUREPARAMETERIPROC, glTextureParameteri);
    GL_GET_PROC_ADR(PFNGLCREATETEXTURESPROC, glCreateTextures);
    GL_GET_PROC_ADR(PFNGLGETINTEGERVPROC, glGetIntegerv);
    GL_GET_PROC_ADR(PFNGLREADPIXELSPROC, glReadPixels);
    GL_GET_PROC_ADR(PFNGLBINDRENDERBUFFERPROC, glBindRenderbuffer);
    GL_GET_PROC_ADR(PFNGLBINDBUFFERPROC, glBindBuffer);
    GL_GET_PROC_ADR(PFNGLBUFFERSTORAGEPROC, glBufferStorage);
    GL_GET_PROC_ADR(PFNGLPROGRAMBINARYPROC, glProgramBinary);
    GL_GET_PROC_ADR(PFNGLGETPROGRAMBINARYPROC, glGetProgramBinary);
    GL_GET_PROC_ADR(PFNGLPROGRAMPARAMETERIPROC, glProgramParameteri);
    GL_GET_PROC_ADR(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer);
}
