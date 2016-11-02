#include "Window.h"
#include "ErrorManager.h"
#include <iostream>

namespace Engine{

    Window::Window()
    {
    }

    Window::~Window()
    {
    }

    int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int newflags){

        Uint32 flags = SDL_WINDOW_OPENGL;

        if(newflags & INVISIBLE){ flags |= SDL_WINDOW_HIDDEN; }
        if(newflags & FULLSCREEN){ flags |= SDL_WINDOW_FULLSCREEN_DESKTOP; }
        if(newflags & BORDERLESS){ flags |= SDL_WINDOW_BORDERLESS; }

        _sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
        if(_sdlWindow == nullptr){
            fatalError("SDL Window could not be created!");
        }

        SDL_GLContext _glcontext = SDL_GL_CreateContext(_sdlWindow);
        if(_glcontext == nullptr){
            fatalError("SDL_GLContext could not be created!");
        }

        GLenum error = glewInit();
        if(error != GLEW_OK){
            fatalError("Could not initialize GLEW");
        }

        std::cout << "*** OPENGL VERSION : " << glGetString(GL_VERSION) << " ***\n";

        glClearColor(0.4f,0.4f,0.8f,1.0f);

        //Set VSync
        SDL_GL_SetSwapInterval(0);

        return 0;
    }

    void Window::swapBuffer(){
        SDL_GL_SwapWindow(_sdlWindow);
    }

}
