#include "Errors.h"
#include <cstdlib>
#include <iostream>
#include <SDL.h>

void fatalError(std::string errorString){
    std::cout << errorString << std::endl;
    std::cout << "Press any key to continue...";
    int _temp;
    std::cin >> _temp;
    SDL_Quit();
    exit(1);
}
