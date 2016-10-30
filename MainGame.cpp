#include <iostream>
#include <string>
#include "MainGame.h"
#include "Errors.h"

MainGame::MainGame(){
    _window = nullptr;
    _screenWidth = 1280;
    _screenHeight = 720;
    _gameState = GameState::PLAY;
    _maxFPS = 60.0f;
}

MainGame::~MainGame(){

}

void MainGame::run(){
    initSystems();

    //_sprite.Init(0.0f, 0.0f, 0.15f, 0.5f, "./textures/Ramza2-SW.png");

    _sprites.push_back(new Sprite());
    _sprites.back()->Init(0.5f, -0.5f, 0.15f, 0.5f, "./textures/Ramza2-SW.png");

    _sprites.push_back(new Sprite());
    _sprites.back()->Init(0.0f, -0.5f, 0.15f, 0.5f, "./textures/Ramza2-SW.png");

    _sprites.push_back(new Sprite());
    _sprites.back()->Init(-0.5f, -0.5f, 0.15f, 0.5f, "./textures/Ramza2-NW.png");

    for(float i = 0; i < 6; i++){
        _sprites.push_back(new Sprite());
        _sprites.back()->Init(-0.95f + (i * 0.35f), 0.0f, 0.15f, 0.5f, "./textures/Ramza2-SW.png");
    }

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
    _colorProgram.OpenShaders("shaders/colorShading.vert","shaders/colorShading.frag");
    _colorProgram.AddAttribute("vertexPosition");
    _colorProgram.AddAttribute("vertexColor");
    _colorProgram.AddAttribute("vertexUV");
    _colorProgram.LinkShaders();
}


void MainGame::Update(){
    while(_gameState != GameState::EXIT){
        //Used to measure frame times.
        float startTicks = SDL_GetTicks();

        Input();
        Draw();
        CalculateFPS();

        //Print every 10 frames
        static int frameCounter = 0;

        frameCounter++;

        if(frameCounter == 10){
            std::cout << _fps << std::endl;
            frameCounter = 0;
        }

        //Limit FPS
        float frameTicks = SDL_GetTicks() - startTicks;
        if(1000.0f / _maxFPS > frameTicks){
            SDL_Delay(1000.0f / _maxFPS - frameTicks);
        }
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
                //std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
                break;
        }
    }
}

void MainGame::Draw(){

    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _colorProgram.Use();

    glActiveTexture(GL_TEXTURE0);

    GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);

    for(int i = 0; i < _sprites.size(); i++){
        _sprites[i]->Draw();
    }

    _colorProgram.Unuse();

    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_GL_SwapWindow(_window);
}

void MainGame::CalculateFPS(){
    static const int NUM_SAMPLES = 10;
    static float frameTimes[NUM_SAMPLES];
    static int curFrame = 0;
    static float prevTicks = SDL_GetTicks();
    float curTicks;

    curTicks = SDL_GetTicks();

    _frameTime = curTicks - prevTicks;
    frameTimes[curFrame % NUM_SAMPLES] = _frameTime;

    prevTicks = curTicks;

    int _count;

    curFrame++;
    if(curFrame <  NUM_SAMPLES){
        _count = curFrame;
    } else {
        _count = NUM_SAMPLES;
    }

    float frameTimeAverage = 0;

    for(int i = 0; i < _count; i++){
        frameTimeAverage += frameTimes[i];
    }

    frameTimeAverage /= _count;

    if(frameTimeAverage > 0){
        _fps = 1000.0f / frameTimeAverage;
    } else {
        _fps = 60.0f;
    }


}




