#include "mouse.h"

namespace SGLR {

    float mouse::m_x = 0;
    float mouse::m_xLast = 0;

    float mouse::m_y = 0;
    float mouse::m_yLast = 0;

    std::array<bool, mouse::m_buttonCount> mouse::buttons;
    std::array<bool, mouse::m_buttonCount> mouse::buttonsLast;

    void mouse::init() {
        std::fill(buttons.begin(), buttons.end(), false);
        std::fill(buttonsLast.begin(), buttonsLast.end(), false);
    }

    void mouse::update() {

        m_xLast = m_x;
        m_yLast = m_y;
        buttonsLast = buttons;

        Uint32 state = SDL_GetMouseState(&m_x, &m_y);
        for (int i = 0; i < m_buttonCount; i++) {

            buttons[i] = state & SDL_BUTTON(i + 1);

        } //endfor

    } //update

    bool mouse::button(int button) {
        if (button >= INPUT_MOUSE_FIRST && button <= INPUT_MOUSE_LAST) {
            return buttons[static_cast<std::array<bool, 5Ui64>::size_type>(button) - 1];
        }

        return false;
    }

    bool mouse::buttondown(int button) {
        if (button >= INPUT_MOUSE_FIRST && button <= INPUT_MOUSE_LAST) {
            return buttonsLast[static_cast<std::array<bool, 5Ui64>::size_type>(button) - 1] && !buttonsLast[static_cast<std::array<bool, 5Ui64>::size_type>(button) - 1];
        }

        return false;
    }

    bool mouse::buttonup(int button) {
        if (button >= INPUT_MOUSE_FIRST && button <= INPUT_MOUSE_LAST) {
            return !buttonsLast[static_cast<std::array<bool, 5Ui64>::size_type>(button) - 1] && buttonsLast[static_cast<std::array<bool, 5Ui64>::size_type>(button) - 1];
        }

        return false;
    }
}