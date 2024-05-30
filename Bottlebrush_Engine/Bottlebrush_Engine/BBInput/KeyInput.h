#ifndef BOTTLEBRUSH_ENGINE_KEYINPUT_H
#define BOTTLEBRUSH_ENGINE_KEYINPUT_H

#include <map>
#include <memory>
#include <vector>

#include "glfw/glfw3.h"

class KeyInput {
 public:
  enum KeyType {
    kKey0 = GLFW_KEY_0,
    kKey1 = GLFW_KEY_1,
    kKey2 = GLFW_KEY_2,
    kKey3 = GLFW_KEY_3,
    kKey4 = GLFW_KEY_4,
    kKey5 = GLFW_KEY_5,
    kKey6 = GLFW_KEY_6,
    kKey7 = GLFW_KEY_7,
    kKey8 = GLFW_KEY_8,
    kKey9 = GLFW_KEY_9,
    kKeyA = GLFW_KEY_A,
    kKeyApostrophe = GLFW_KEY_APOSTROPHE,
    kKeyB = GLFW_KEY_B,
    kKeyBackslash = GLFW_KEY_BACKSLASH,
    kKeyBackspace = GLFW_KEY_BACKSPACE,
    kKeyC = GLFW_KEY_C,
    kKeyCapsLock = GLFW_KEY_CAPS_LOCK,
    kKeyComma = GLFW_KEY_COMMA,
    kKeyD = GLFW_KEY_D,
    kKeyDelete = GLFW_KEY_DELETE,
    kKeyDown = GLFW_KEY_DOWN,
    kKeyE = GLFW_KEY_E,
    kKeyEnd = GLFW_KEY_END,
    kKeyEnter = GLFW_KEY_ENTER,
    kKeyEqual = GLFW_KEY_EQUAL,
    kKeyEscape = GLFW_KEY_ESCAPE,
    kKeyF = GLFW_KEY_F,
    kKeyF1 = GLFW_KEY_F1,
    kKeyF10 = GLFW_KEY_F10,
    kKeyF11 = GLFW_KEY_F11,
    kKeyF12 = GLFW_KEY_F12,
    kKeyF2 = GLFW_KEY_F2,
    kKeyF3 = GLFW_KEY_F3,
    kKeyF4 = GLFW_KEY_F4,
    kKeyF5 = GLFW_KEY_F5,
    kKeyF6 = GLFW_KEY_F6,
    kKeyF7 = GLFW_KEY_F7,
    kKeyF8 = GLFW_KEY_F8,
    kKeyF9 = GLFW_KEY_F9,
    kKeyG = GLFW_KEY_G,
    kKeyGraveAccent = GLFW_KEY_GRAVE_ACCENT,
    kKeyH = GLFW_KEY_H,
    kKeyHome = GLFW_KEY_HOME,
    kKeyI = GLFW_KEY_I,
    kKeyInsert = GLFW_KEY_INSERT,
    kKeyJ = GLFW_KEY_J,
    kKeyK = GLFW_KEY_K,
    kKeyL = GLFW_KEY_L,
    kKeyLast = GLFW_KEY_LAST,
    kKeyLeft = GLFW_KEY_LEFT,
    kKeyLeftAlt = GLFW_KEY_LEFT_ALT,
    kKeyLeftBracket = GLFW_KEY_LEFT_BRACKET,
    kKeyLeftControl = GLFW_KEY_LEFT_CONTROL,
    kKeyLeftShift = GLFW_KEY_LEFT_SHIFT,
    kKeyLeftSuper = GLFW_KEY_LEFT_SUPER,
    kKeyM = GLFW_KEY_M,
    kKeyMenu = GLFW_KEY_MENU,
    kKeyMinus = GLFW_KEY_MINUS,
    kKeyN = GLFW_KEY_N,
    kKeyNumLock = GLFW_KEY_NUM_LOCK,
    kKeyO = GLFW_KEY_O,
    kKeyP = GLFW_KEY_P,
    kKeyPad0 = GLFW_KEY_KP_0,
    kKeyPad1 = GLFW_KEY_KP_1,
    kKeyPad2 = GLFW_KEY_KP_2,
    kKeyPad3 = GLFW_KEY_KP_3,
    kKeyPad4 = GLFW_KEY_KP_4,
    kKeyPad5 = GLFW_KEY_KP_5,
    kKeyPad6 = GLFW_KEY_KP_6,
    kKeyPad7 = GLFW_KEY_KP_7,
    kKeyPad8 = GLFW_KEY_KP_8,
    kKeyPad9 = GLFW_KEY_KP_9,
    kKeyPadAdd = GLFW_KEY_KP_ADD,
    kKeyPadDecimal = GLFW_KEY_KP_DECIMAL,
    kKeyPadDivide = GLFW_KEY_KP_DIVIDE,
    kKeyPadEnter = GLFW_KEY_KP_ENTER,
    kKeyPadEqual = GLFW_KEY_KP_EQUAL,
    kKeyPadMultiply = GLFW_KEY_KP_MULTIPLY,
    kKeyPadSubtract = GLFW_KEY_KP_SUBTRACT,
    kKeyPageDown = GLFW_KEY_PAGE_DOWN,
    kKeyPageUp = GLFW_KEY_PAGE_UP,
    kKeyPause = GLFW_KEY_PAUSE,
    kKeyPeriod = GLFW_KEY_PERIOD,
    kKeyPrintScreen = GLFW_KEY_PRINT_SCREEN,
    kKeyQ = GLFW_KEY_Q,
    kKeyR = GLFW_KEY_R,
    kKeyRight = GLFW_KEY_RIGHT,
    kKeyRightAlt = GLFW_KEY_RIGHT_ALT,
    kKeyRightBracket = GLFW_KEY_RIGHT_BRACKET,
    kKeyRightControl = GLFW_KEY_RIGHT_CONTROL,
    kKeyRightShift = GLFW_KEY_RIGHT_SHIFT,
    kKeyRightSuper = GLFW_KEY_RIGHT_SUPER,
    kKeyS = GLFW_KEY_S,
    kKeyScrollLock = GLFW_KEY_SCROLL_LOCK,
    kKeySemicolon = GLFW_KEY_SEMICOLON,
    kKeySlash = GLFW_KEY_SLASH,
    kKeySpace = GLFW_KEY_SPACE,
    kKeyT = GLFW_KEY_T,
    kKeyTab = GLFW_KEY_TAB,
    kKeyU = GLFW_KEY_U,
    kKeyUnknown = GLFW_KEY_UNKNOWN,
    kKeyUp = GLFW_KEY_UP,
    kKeyV = GLFW_KEY_V,
    kKeyW = GLFW_KEY_W,
    kKeyWorld1 = GLFW_KEY_WORLD_1,
    kKeyWorld2 = GLFW_KEY_WORLD_2,
    kKeyX = GLFW_KEY_X,
    kKeyY = GLFW_KEY_Y,
    kKeyZ = GLFW_KEY_Z
  };

  enum KeyModifier {
    kModNone = 0x0000,
    kModAlt = GLFW_MOD_ALT,
    kModCapsLock = GLFW_MOD_CAPS_LOCK,
    kModControl = GLFW_MOD_CONTROL,
    kModNumLock = GLFW_MOD_NUM_LOCK,
    kModShift = GLFW_MOD_SHIFT,
    kModSuper = GLFW_MOD_SUPER
  };

  enum KeyState {
    kNone = -1,
    kPress = GLFW_PRESS,
    kRelease = GLFW_RELEASE,
    kRepeat = GLFW_REPEAT
  };

  KeyInput(const std::vector<KeyType>& keys_to_monitor);

  ~KeyInput();

  [[nodiscard]] KeyState GetKeyState(KeyType key) const;
  [[nodiscard]] const std::vector<KeyType>& GetKeyTypes() const;
  void SetKeyState(KeyType key, KeyState state);

 private:
  std::map<KeyType, KeyState> keys_;
  std::vector<KeyType> keys_to_monitor_;
};

#endif  // BOTTLEBRUSH_ENGINE_KEYINPUT_H
