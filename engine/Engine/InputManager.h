#pragma once
#include <unordered_map>

namespace Engine {

    class InputManager
    {
        public:
            InputManager();
            ~InputManager();

            void KeyPress(unsigned int keyID);
            void KeyRelease(unsigned int keyID);
            bool IsKeyDown(unsigned int keyID);

        private:
            std::unordered_map<unsigned int, bool> _keyMap;
    };

}
