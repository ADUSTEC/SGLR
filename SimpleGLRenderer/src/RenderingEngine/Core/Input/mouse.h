#pragma once

#include <SDL3/SDL.h>
#include <array>

namespace SGLR {

        class mouse {

        public:
            static void init();
            static void update();

            inline static float x() { return m_x; }
            inline static float y() { return m_y; }

            inline static float dx() { return m_x - m_xLast; }
            inline static float dy() { return m_y - m_yLast; }

            static bool button(int button);
            static bool buttondown(int button);
            static bool buttonup(int button);

            static void hide() { SDL_HideCursor(); }
			static void show() { SDL_ShowCursor(); }

            static void lock() { SDL_SetRelativeMouseMode(SDL_TRUE); }
            static void unlock() { SDL_SetRelativeMouseMode(SDL_FALSE); }

            static void setPosInWindow(SDL_Window* window, float x, float y) { SDL_WarpMouseInWindow(window, x, y); }

        private:
            constexpr static const int m_buttonCount = 5;

            static float m_x, m_xLast;
            static float m_y, m_yLast;

            static std::array<bool, m_buttonCount> buttons;
            static std::array<bool, m_buttonCount> buttonsLast;
        };
}

enum MOUSEINPUTCODES
{
    INPUT_MOUSE_FIRST = 1,
    INPUT_MOUSE_LEFT = INPUT_MOUSE_FIRST,
    INPUT_MOUSE_MIDDLE = 2,
    INPUT_MOUSE_RIGHT = 3,
    INPUT_MOUSE_X1 = 4,
    INPUT_MOUSE_X2 = 5,
    INPUT_MOUSE_LAST = 5
};