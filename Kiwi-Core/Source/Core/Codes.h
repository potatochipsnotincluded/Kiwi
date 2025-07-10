#pragma once

typedef enum {
    KW_KEY_NULL = 0,        // Key: NULL, used for no key pressed
    KW_KEY_APOSTROPHE = 39,       // Key: '
    KW_KEY_COMMA = 44,       // Key: ,
    KW_KEY_MINUS = 45,       // Key: -
    KW_KEY_PERIOD = 46,       // Key: .
    KW_KEY_SLASH = 47,       // Key: /
    KW_KEY_ZERO = 48,       // Key: 0
    KW_KEY_ONE = 49,       // Key: 1
    KW_KEY_TWO = 50,       // Key: 2
    KW_KEY_THREE = 51,       // Key: 3
    KW_KEY_FOUR = 52,       // Key: 4
    KW_KEY_FIVE = 53,       // Key: 5
    KW_KEY_SIX = 54,       // Key: 6
    KW_KEY_SEVEN = 55,       // Key: 7
    KW_KEY_EIGHT = 56,       // Key: 8
    KW_KEY_NINE = 57,       // Key: 9
    KW_KEY_SEMICOLON = 59,       // Key: ;
    KW_KEY_EQUAL = 61,       // Key: =
    KW_KEY_A = 65,       // Key: A | a
    KW_KEY_B = 66,       // Key: B | b
    KW_KEY_C = 67,       // Key: C | c
    KW_KEY_D = 68,       // Key: D | d
    KW_KEY_E = 69,       // Key: E | e
    KW_KEY_F = 70,       // Key: F | f
    KW_KEY_G = 71,       // Key: G | g
    KW_KEY_H = 72,       // Key: H | h
    KW_KEY_I = 73,       // Key: I | i
    KW_KEY_J = 74,       // Key: J | j
    KW_KEY_K = 75,       // Key: K | k
    KW_KEY_L = 76,       // Key: L | l
    KW_KEY_M = 77,       // Key: M | m
    KW_KEY_N = 78,       // Key: N | n
    KW_KEY_O = 79,       // Key: O | o
    KW_KEY_P = 80,       // Key: P | p
    KW_KEY_Q = 81,       // Key: Q | q
    KW_KEY_R = 82,       // Key: R | r
    KW_KEY_S = 83,       // Key: S | s
    KW_KEY_T = 84,       // Key: T | t
    KW_KEY_U = 85,       // Key: U | u
    KW_KEY_V = 86,       // Key: V | v
    KW_KEY_W = 87,       // Key: W | w
    KW_KEY_X = 88,       // Key: X | x
    KW_KEY_Y = 89,       // Key: Y | y
    KW_KEY_Z = 90,       // Key: Z | z
    KW_KEY_LEFT_BRACKET = 91,       // Key: [
    KW_KEY_BACKSLASH = 92,       // Key: '\'
    KW_KEY_RIGHT_BRACKET = 93,       // Key: ]
    KW_KEY_GRAVE = 96,       // Key: `
    KW_KEY_SPACE = 32,       // Key: Space
    KW_KEY_ESCAPE = 256,      // Key: Esc
    KW_KEY_ENTER = 257,      // Key: Enter
    KW_KEY_TAB = 258,      // Key: Tab
    KW_KEY_BACKSPACE = 259,      // Key: Backspace
    KW_KEY_INSERT = 260,      // Key: Ins
    KW_KEY_DELETE = 261,      // Key: Del
    KW_KEY_RIGHT = 262,      // Key: Cursor right
    KW_KEY_LEFT = 263,      // Key: Cursor left
    KW_KEY_DOWN = 264,      // Key: Cursor down
    KW_KEY_UP = 265,      // Key: Cursor up
    KW_KEY_PAGE_UP = 266,      // Key: Page up
    KW_KEY_PAGE_DOWN = 267,      // Key: Page down
    KW_KEY_HOME = 268,      // Key: Home
    KW_KEY_END = 269,      // Key: End
    KW_KEY_CAPS_LOCK = 280,      // Key: Caps lock
    KW_KEY_SCROLL_LOCK = 281,      // Key: Scroll down
    KW_KEY_NUM_LOCK = 282,      // Key: Num lock
    KW_KEY_PRINT_SCREEN = 283,      // Key: Print screen
    KW_KEY_PAUSE = 284,      // Key: Pause
    KW_KEY_F1 = 290,      // Key: F1
    KW_KEY_F2 = 291,      // Key: F2
    KW_KEY_F3 = 292,      // Key: F3
    KW_KEY_F4 = 293,      // Key: F4
    KW_KEY_F5 = 294,      // Key: F5
    KW_KEY_F6 = 295,      // Key: F6
    KW_KEY_F7 = 296,      // Key: F7
    KW_KEY_F8 = 297,      // Key: F8
    KW_KEY_F9 = 298,      // Key: F9
    KW_KEY_F10 = 299,      // Key: F10
    KW_KEY_F11 = 300,      // Key: F11
    KW_KEY_F12 = 301,      // Key: F12
    KW_KEY_LEFT_SHIFT = 340,      // Key: Shift left
    KW_KEY_LEFT_CONTROL = 341,      // Key: Control left
    KW_KEY_LEFT_ALT = 342,      // Key: Alt left
    KW_KEY_LEFT_SUPER = 343,      // Key: Super left
    KW_KEY_RIGHT_SHIFT = 344,      // Key: Shift right
    KW_KEY_RIGHT_CONTROL = 345,      // Key: Control right
    KW_KEY_RIGHT_ALT = 346,      // Key: Alt right
    KW_KEY_RIGHT_SUPER = 347,      // Key: Super right
    KW_KEY_KB_MENU = 348,      // Key: KB menu
    KW_KEY_KP_0 = 320,      // Key: Keypad 0
    KW_KEY_KP_1 = 321,      // Key: Keypad 1
    KW_KEY_KP_2 = 322,      // Key: Keypad 2
    KW_KEY_KP_3 = 323,      // Key: Keypad 3
    KW_KEY_KP_4 = 324,      // Key: Keypad 4
    KW_KEY_KP_5 = 325,      // Key: Keypad 5
    KW_KEY_KP_6 = 326,      // Key: Keypad 6
    KW_KEY_KP_7 = 327,      // Key: Keypad 7
    KW_KEY_KP_8 = 328,      // Key: Keypad 8
    KW_KEY_KP_9 = 329,      // Key: Keypad 9
    KW_KEY_KP_DECIMAL = 330,      // Key: Keypad .
    KW_KEY_KP_DIVIDE = 331,      // Key: Keypad /
    KW_KEY_KP_MULTIPLY = 332,      // Key: Keypad *
    KW_KEY_KP_SUBTRACT = 333,      // Key: Keypad -
    KW_KEY_KP_ADD = 334,      // Key: Keypad +
    KW_KEY_KP_ENTER = 335,      // Key: Keypad Enter
    KW_KEY_KP_EQUAL = 336,      // Key: Keypad =
    KW_KEY_BACK = 4,        // Key: Android back button
    KW_KEY_MENU = 5,        // Key: Android menu button
    KW_KEY_VOLUME_UP = 24,       // Key: Android volume up button
    KW_KEY_VOLUME_DOWN = 25        // Key: Android volume down button
} KiwiKeyboardKey;

// Mouse buttons
typedef enum {
    KW_MOUSE_BUTTON_LEFT = 0,       // Mouse button left
    KW_MOUSE_BUTTON_RIGHT = 1,       // Mouse button right
    KW_MOUSE_BUTTON_MIDDLE = 2,       // Mouse button middle (pressed wheel)
    KW_MOUSE_BUTTON_SIDE = 3,       // Mouse button side (advanced mouse device)
    KW_MOUSE_BUTTON_EXTRA = 4,       // Mouse button extra (advanced mouse device)
    KW_MOUSE_BUTTON_FORWARD = 5,       // Mouse button forward (advanced mouse device)
    KW_MOUSE_BUTTON_BACK = 6,       // Mouse button back (advanced mouse device)
} KiwiMouseButton;

// Gamepad buttons
typedef enum {
    KW_GAMEPAD_BUTTON_UNKNOWN = 0,         // Unknown button, just for error checking
    KW_GAMEPAD_BUTTON_LEFT_FACE_UP,        // Gamepad left DPAD up button
    KW_GAMEPAD_BUTTON_LEFT_FACE_RIGHT,     // Gamepad left DPAD right button
    KW_GAMEPAD_BUTTON_LEFT_FACE_DOWN,      // Gamepad left DPAD down button
    KW_GAMEPAD_BUTTON_LEFT_FACE_LEFT,      // Gamepad left DPAD left button
    KW_GAMEPAD_BUTTON_RIGHT_FACE_UP,       // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
    KW_GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,    // Gamepad right button right (i.e. PS3: Circle, Xbox: B)
    KW_GAMEPAD_BUTTON_RIGHT_FACE_DOWN,     // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
    KW_GAMEPAD_BUTTON_RIGHT_FACE_LEFT,     // Gamepad right button left (i.e. PS3: Square, Xbox: X)
    KW_GAMEPAD_BUTTON_LEFT_TRIGGER_1,      // Gamepad top/back trigger left (first), it could be a trailing button
    KW_GAMEPAD_BUTTON_LEFT_TRIGGER_2,      // Gamepad top/back trigger left (second), it could be a trailing button
    KW_GAMEPAD_BUTTON_RIGHT_TRIGGER_1,     // Gamepad top/back trigger right (first), it could be a trailing button
    KW_GAMEPAD_BUTTON_RIGHT_TRIGGER_2,     // Gamepad top/back trigger right (second), it could be a trailing button
    KW_GAMEPAD_BUTTON_MIDDLE_LEFT,         // Gamepad center buttons, left one (i.e. PS3: Select)
    KW_GAMEPAD_BUTTON_MIDDLE,              // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
    KW_GAMEPAD_BUTTON_MIDDLE_RIGHT,        // Gamepad center buttons, right one (i.e. PS3: Start)
    KW_GAMEPAD_BUTTON_LEFT_THUMB,          // Gamepad joystick pressed button left
    KW_GAMEPAD_BUTTON_RIGHT_THUMB          // Gamepad joystick pressed button right
} KiwiGamepadButton;

// Gamepad axis
typedef enum {
    KW_GAMEPAD_AXIS_LEFT_X = 0,     // Gamepad left stick X axis
    KW_GAMEPAD_AXIS_LEFT_Y = 1,     // Gamepad left stick Y axis
    KW_GAMEPAD_AXIS_RIGHT_X = 2,     // Gamepad right stick X axis
    KW_GAMEPAD_AXIS_RIGHT_Y = 3,     // Gamepad right stick Y axis
    KW_GAMEPAD_AXIS_LEFT_TRIGGER = 4,     // Gamepad back trigger left, pressure level: [1..-1]
    KW_GAMEPAD_AXIS_RIGHT_TRIGGER = 5      // Gamepad back trigger right, pressure level: [1..-1]
} KiwiGamepadAxis;