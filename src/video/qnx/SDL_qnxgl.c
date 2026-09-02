/*
  Simple DirectMedia Layer
  Copyright (C) 2026 BlackBerry Limited

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "SDL_internal.h"
#include "SDL_qnx.h"

#include "../SDL_egl_c.h"

// static EGLDisplay   egl_disp;

// struct DummyConfig
// {
//     int red_size;
//     int green_size;
//     int blue_size;
//     int alpha_size;
//     int native_id;
// };

// static struct DummyConfig getDummyConfigFromScreenSettings(int format)
// {
//     struct DummyConfig dummyConfig= {};

//     dummyConfig.native_id = format;
//     switch (format) {
//          case SCREEN_FORMAT_RGBX4444:
//             dummyConfig.red_size = 4;
//             dummyConfig.green_size = 4;
//             dummyConfig.blue_size = 4;
//             dummyConfig.alpha_size = 4;
//             break;
//          case SCREEN_FORMAT_RGBA5551:
//             dummyConfig.red_size = 5;
//             dummyConfig.green_size = 5;
//             dummyConfig.blue_size = 5;
//             dummyConfig.alpha_size = 1;
//             break;
//          case SCREEN_FORMAT_RGB565:
//             dummyConfig.red_size = 5;
//             dummyConfig.green_size = 6;
//             dummyConfig.blue_size = 5;
//             dummyConfig.alpha_size = 0;
//             break;
//          case SCREEN_FORMAT_RGB888:
//             dummyConfig.red_size = 8;
//             dummyConfig.green_size = 8;
//             dummyConfig.blue_size = 8;
//             dummyConfig.alpha_size = 0;
//             break;
//             case SCREEN_FORMAT_BGRA8888:
//             case SCREEN_FORMAT_BGRX8888:
//             case SCREEN_FORMAT_RGBA8888:
//          case SCREEN_FORMAT_RGBX8888:
//             dummyConfig.red_size = 8;
//             dummyConfig.green_size = 8;
//             dummyConfig.blue_size = 8;
//             dummyConfig.alpha_size = 8;
//             break;
//             default:
//                 break;
//     }
//     return dummyConfig;
// }

// static EGLConfig chooseConfig(struct DummyConfig dummyConfig, EGLConfig* egl_configs, EGLint egl_num_configs)
// {
//    EGLConfig glConfig = (EGLConfig)0;

//     for (size_t ii = 0; ii < egl_num_configs; ii++) {
//         EGLint val;

//         eglGetConfigAttrib(egl_disp, egl_configs[ii], EGL_SURFACE_TYPE, &val);
//         if (!(val & EGL_WINDOW_BIT)) {
//             continue;
//         }

//         eglGetConfigAttrib(egl_disp, egl_configs[ii], EGL_RENDERABLE_TYPE, &val);
//         if (!(val & EGL_OPENGL_ES2_BIT)) {
//             continue;
//         }

//         eglGetConfigAttrib(egl_disp, egl_configs[ii], EGL_DEPTH_SIZE, &val);
//         if (val == 0) {
//             continue;
//         }

//         eglGetConfigAttrib(egl_disp, egl_configs[ii], EGL_RED_SIZE, &val);
//         if (val != dummyConfig.red_size) {
//            continue;
//         }

//         eglGetConfigAttrib(egl_disp, egl_configs[ii], EGL_GREEN_SIZE, &val);
//         if (val != dummyConfig.green_size) {
//            continue;
//         }

//         eglGetConfigAttrib(egl_disp, egl_configs[ii], EGL_BLUE_SIZE, &val);
//         if (val != dummyConfig.blue_size) {
//            continue;
//         }

//         eglGetConfigAttrib(egl_disp, egl_configs[ii], EGL_ALPHA_SIZE, &val);
//         if (val != dummyConfig.alpha_size) {
//             continue;
//         }
//         if(!glConfig)
//         {
//             glConfig = egl_configs[ii];
//         }

//         eglGetConfigAttrib(egl_disp, egl_configs[ii], EGL_NATIVE_VISUAL_ID, &val);
//         if ((val != 0) && (val == dummyConfig.native_id)) {
//             return egl_configs[ii];
//         }
//     }
//     return glConfig;
// }

// /**
//  * Detertmines the pixel format to use based on the current display and EGL
//  * configuration.
//  * @param   egl_conf    EGL configuration to use
//  * @return  A SCREEN_FORMAT* constant for the pixel format to use
//  */
// static int chooseFormat(EGLConfig egl_conf)
// {
//     EGLint buffer_bit_depth;
//     EGLint alpha_bit_depth;

//     eglGetConfigAttrib(egl_disp, egl_conf, EGL_BUFFER_SIZE, &buffer_bit_depth);
//     eglGetConfigAttrib(egl_disp, egl_conf, EGL_ALPHA_SIZE, &alpha_bit_depth);

//     switch (buffer_bit_depth) {
//         case 32:
//             return SCREEN_FORMAT_RGBX8888;
//         case 24:
//             return SCREEN_FORMAT_RGB888;
//         case 16:
//             switch (alpha_bit_depth) {
//                 case 4:
//                     return SCREEN_FORMAT_RGBX4444;
//                 case 1:
//                     return SCREEN_FORMAT_RGBA5551;
//                 default:
//                     return SCREEN_FORMAT_RGB565;
//             }
//         default:
//             return 0;
//     }
// }

// /**
//  * Enumerates the supported EGL configurations and chooses a suitable one.
//  * @param[out]  pformat The chosen pixel format
//  * @return true if successful, false on error
//  */
// bool glInitConfig(SDL_WindowData *impl, int *pformat)
// {
//     EGLConfig egl_conf = (EGLConfig)0;
//     EGLConfig *egl_configs;
//     EGLint egl_num_configs;
//     EGLBoolean rc;
//     struct DummyConfig dummyconfig = {};

//     // Determine the number of configurations.
//     rc = eglGetConfigs(egl_disp, NULL, 0, &egl_num_configs);
//     if (rc != EGL_TRUE) {
//         return false;
//     }

//     if (egl_num_configs == 0) {
//         return false;
//     }

//     // Allocate enough memory for all configurations.
//     egl_configs = SDL_malloc(egl_num_configs * sizeof(*egl_configs));
//     if (!egl_configs) {
//         return false;
//     }

//     // Get the list of configurations.
//     rc = eglGetConfigs(egl_disp, egl_configs, egl_num_configs,
//                        &egl_num_configs);
//     if (rc != EGL_TRUE) {
//         SDL_free(egl_configs);
//         return false;
//     }

//     dummyconfig = getDummyConfigFromScreenSettings(*pformat);
//     egl_conf = chooseConfig(dummyconfig, egl_configs, egl_num_configs);
//     *pformat = chooseFormat(egl_conf);

//     SDL_free(egl_configs);
//     impl->conf = egl_conf;

//     return true;
// }

/**
 * Initializes the EGL library.
 * @param   SDL_VideoDevice *_this
 * @param   egl_path    Path to EGL dll.
 * @return  true if successful, false on error
 */
bool QNX_GLES_LoadLibrary(SDL_VideoDevice *_this, const char *egl_path)
{
    return SDL_EGL_LoadLibrary(_this, egl_path, EGL_DEFAULT_DISPLAY);
}

/**
 * Finds the address of an EGL extension function.
 * @param   proc    Function name
 * @return  Function address
 */
SDL_FunctionPointer QNX_GLES_GetProcAddress(SDL_VideoDevice *_this, const char *proc)
{
    return SDL_EGL_GetProcAddressInternal(_this, proc);
}

/**
 * Associates the given window with the necessary EGL structures for drawing and
 * displaying content.
 * @param   SDL_VideoDevice *_this
 * @param   window  The SDL window to create the context for
 * @return  A pointer to the created context, if successful, NULL on error
 */
// SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
// {
//     SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
//     EGLContext      context;
//     EGLSurface      surface;

//     struct {
//         EGLint client_version[2];
//         EGLint none;
//     } egl_ctx_attr = {
//         .client_version = { EGL_CONTEXT_CLIENT_VERSION, 2 },
//         .none = EGL_NONE
//     };

//     struct {
//         EGLint render_buffer[2];
//         EGLint none;
//     } egl_surf_attr = {
//         .render_buffer = { EGL_RENDER_BUFFER, EGL_BACK_BUFFER },
//         .none = EGL_NONE
//     };

//     context = eglCreateContext(egl_disp, impl->conf, EGL_NO_CONTEXT,
//                                (EGLint *)&egl_ctx_attr);
//     if (context == EGL_NO_CONTEXT) {
//         return NULL;
//     }

//     surface = eglCreateWindowSurface(egl_disp, impl->conf,
//                                      (EGLNativeWindowType)impl->window,
//                                      (EGLint *)&egl_surf_attr);
//     if (surface == EGL_NO_SURFACE) {
//         return NULL;
//     }

//     eglMakeCurrent(egl_disp, surface, surface, context);

//     impl->egl_surface = surface;
//     impl->context = context;

//     SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, impl->egl_surface);

//     return context;
// }

/**
 * Sets a new value for the number of frames to display before swapping buffers.
 * @param   SDL_VideoDevice *_this
 * @param   interval    New interval value
 * @return  true if successful, false on error
 */
bool QNX_GLES_SetSwapInterval(SDL_VideoDevice *_this, int interval)
{
    return SDL_EGL_SetSwapInterval(_this, interval);
}

/**
 * Gets the value for the number of frames to display before swapping buffers.
 * @param   SDL_VideoDevice *_this
 * @param   *interval    Interval value
 * @return  true if successful, false on error
 */
bool QNX_GLES_GetSwapInterval(SDL_VideoDevice *_this, int *interval)
{
    return SDL_EGL_GetSwapInterval(_this, interval);
}

/**
 * Swaps the EGL buffers associated with the given window
 * @param   SDL_VideoDevice *_this
 * @param   window  Window to swap buffers for
 * @return  true if successful, false on error
 */
bool QNX_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    {
        if (impl->resize) {
            EGLSurface surface;
            // TODO: Is this needed?
            // struct {
            //     EGLint render_buffer[2];
            //     EGLint none;
            // } egl_surf_attr = {
            //     .render_buffer = { EGL_RENDER_BUFFER, EGL_BACK_BUFFER },
            //     .none = EGL_NONE
            // };

            if (!SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, impl->context)) {
                return false;
            }
            SDL_EGL_DestroySurface(_this, impl->egl_surface);

            surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
            if (surface == EGL_NO_SURFACE) {
                return false;
            }

            if (!SDL_EGL_MakeCurrent(_this, surface, impl->context)) {
                return false;
            }

            impl->egl_surface = surface;
            impl->resize = 0;
        }
    }

    return SDL_EGL_SwapBuffers(_this, impl->egl_surface);
}

/**
 * Destroys a context.
 * @param   SDL_VideoDevice *_this
 * @param   context The context to destroy
 */
bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    return SDL_EGL_DestroyContext(_this, context);
}

/**
 * Terminates access to the EGL library.
 * @param   SDL_VideoDevice *_this
 */
void QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}

SDL_EGL_MakeCurrent_impl(QNX)
SDL_EGL_CreateContext_impl(QNX)
