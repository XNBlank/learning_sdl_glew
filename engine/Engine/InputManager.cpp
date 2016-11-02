#include "InputManager.h"

namespace Engine {

    InputManager::InputManager()
    {
    }

    InputManager::~InputManager()
    {
    }

    void InputManager::KeyPress(unsigned int keyID) {
        _keyMap[keyID] = true;
    }
    void InputManager::KeyRelease(unsigned int keyID) {
        _keyMap[keyID] = false;
    }
    bool InputManager::IsKeyDown(unsigned int keyID) {
        auto it = _keyMap.find(keyID);

        if(it != _keyMap.end()){
            return it->second;
        } else {
            return false;
        }
    }

}
