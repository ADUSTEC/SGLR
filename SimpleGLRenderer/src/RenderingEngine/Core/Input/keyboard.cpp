#include "keyboard.h"

namespace SGLR { 

  std::array<bool, keyboard::m_keyCount> keyboard::keys;
  std::array<bool, keyboard::m_keyCount> keyboard::keysLast;

  void keyboard::init() {
    std::fill(keys.begin(), keys.end(), false);
    std::fill(keysLast.begin(), keysLast.end(), false);
  }

  void keyboard::update() {

    keysLast = keys;
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    for (int i = INPUT_KEY_FIRST; i < m_keyCount; i++) {

      keys[i] = state[i];

    } //endfor
    
  } //update

  bool keyboard::key(int key) {
    if(key >= INPUT_KEY_FIRST && key <= m_keyCount) {
      return keys[key];
    }

    return false;
  }

  bool keyboard::keydown(int key) {
    if(key >= INPUT_KEY_FIRST && key <= m_keyCount) {
      return keys[key] && !keysLast[key];
    }

    return false;
  }

  bool keyboard::keyup(int key) {
    if(key >= INPUT_KEY_FIRST && key <= m_keyCount) {
      return !keys[key] && keysLast[key];
    }

    return false;
  }

}