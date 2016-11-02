#include <iostream>
#include <string>
#include "MainGame.h"
#include <Engine/ErrorManager.h>
#include <Engine/ResourceManager.h>


MainGame::MainGame(){
    _screenWidth = 1280;
    _screenHeight = 720;
    _gameState = GameState::PLAY;
    _maxFPS = 60.0f;
    _camera2D.Init(_screenWidth,_screenHeight);
}

MainGame::~MainGame(){

}

void MainGame::run(){
    InitSystems();

    Update();
}

void MainGame::InitSystems(){

    Engine::Init();

    _window.create("Tactics Engine", _screenWidth, _screenHeight, 0);

    InitShaders();
    _spriteBatch.Init();
    _fpsLimiter.Init(_maxFPS);
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
        _fpsLimiter.Begin();

        Input();

        _camera2D.Update();

        Draw();

        _fps = _fpsLimiter.End();


        //Print every 10 frames
        static int frameCounter = 0;

        frameCounter++;
        if(frameCounter == 60){
            std::cout << _fps << std::endl;
            frameCounter = 0;
        }
    }
}


void MainGame::Input(){
    SDL_Event evnt;

    const float CAMERA_SPEED = 25.0f;
    const float SCALE_SPEED = 0.02f;

    while (SDL_PollEvent(&evnt)){
        switch(evnt.type){
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                //std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
                break;
            case SDL_KEYDOWN:
                _inputManager.KeyPress(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _inputManager.KeyRelease(evnt.key.keysym.sym);
                break;


        }
    }

    if(_inputManager.IsKeyDown(SDLK_w)){
        _camera2D.setPosition(_camera2D.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
    }
    if(_inputManager.IsKeyDown(SDLK_a)){
        _camera2D.setPosition(_camera2D.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
    }
    if(_inputManager.IsKeyDown(SDLK_s)){
        _camera2D.setPosition(_camera2D.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
    }
    if(_inputManager.IsKeyDown(SDLK_d)){
        _camera2D.setPosition(_camera2D.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
    }
    if(_inputManager.IsKeyDown(SDLK_q)){
        _camera2D.setScale(_camera2D.getScale() + SCALE_SPEED);
    }
    if(_inputManager.IsKeyDown(SDLK_e)){
        _camera2D.setScale(_camera2D.getScale() - SCALE_SPEED);
    }

}


void MainGame::Draw(){

    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _colorProgram.Use();

    //Using Texture Unit 0
    glActiveTexture(GL_TEXTURE0);

    GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);

    //Set the camera matrix
    GLint pLocation = _colorProgram.getUniformLocation("P");
    glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();

    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

    _spriteBatch.Begin();

    glm::vec4 pos(0.0f,0.0f,36.0f,74.0f);
    glm::vec4 uv(0.0f,0.0f,1.0f,1.0f);
    static Engine::GLTexture texture = Engine::ResourceManager::getTexture("./textures/Ramza2-SW.png");
    Engine::Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

    int wrap = 5;
    int yplus = 0;
    int xplus = 0;

    //Begin Spritebatch
    for(int i = 0; i < 15; i++){
        if(wrap == 0){
            yplus--;
            xplus = 0;
            wrap = 5;
        }
        _spriteBatch.Draw(pos + (glm::vec4(xplus * 36, yplus * -74,0,0)), uv, texture.id, 0.0f, color);
        xplus++;
        wrap--;
    }


    _spriteBatch.End();

    _spriteBatch.Render();

    _colorProgram.Unuse();

    glBindTexture(GL_TEXTURE_2D, 0);

    _window.swapBuffer();
}




