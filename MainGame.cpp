#include <iostream>
#include <string>
#include "MainGame.h"
#include "Errors.h"

MainGame::MainGame(){
    _window = nullptr;
    _screenWidth = 1280;
    _screenHeight = 720;
    _gameState = GameState::PLAY;
}

MainGame::~MainGame(){

}

void MainGame::run(){
    initSystems();

    _sprite.Init(-1.0f, -1.0f, 1.0f, 1.0f);

    Update();
}

void MainGame::initSystems(){
    //Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow("Tactics Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
    if(_window == nullptr){
        fatalError("SDL Window could not be created!");
    }

    SDL_GLContext _glcontext = SDL_GL_CreateContext(_window);
    if(_glcontext == nullptr){
        fatalError("SDL_GLContext could not be created!");
    }

    GLenum error = glewInit();
    if(error != GLEW_OK){
        fatalError("Could not initialize GLEW");
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    glClearColor(0.4f,0.4f,0.8f,1.0f);

    InitShaders();
}

void MainGame::InitShaders()
{
    _colorProgram.OpenShaders("shaders/colorShading.vertex","shaders/colorShading.frag");
    _colorProgram.AddAttribute("vertexPosition");
    _colorProgram.LinkShaders();
}


void MainGame::Update(){
    while(_gameState != GameState::EXIT){
        Input();
        Draw();
    }
}


void MainGame::Input(){
    SDL_Event evnt;
    while (SDL_PollEvent(&evnt)){
        switch(evnt.type){
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
                break;
        }
    }
}

void MainGame::Draw(){
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _colorProgram.Use();

    _sprite.Draw();

    _colorProgram.Unuse();

    SDL_GL_SwapWindow(_window);
}
