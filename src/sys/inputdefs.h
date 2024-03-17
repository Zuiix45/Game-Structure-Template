#pragma once

/**
 * @brief This file contains the definitions of the input events and keys. Copy of GLFW's definitions.
 * 
 */

typedef int State; /**< RELEASE, PRESS, REPEAT */
typedef int Hat; /**< Hat States on joystick */
typedef int Key; /**< Key codes */
typedef int Scancode; /**< Scancode */
typedef int Mod; /**< Modifier keys */
typedef int MouseButton; /**< Mouse buttons */
typedef int Joystick; /**< Joystick IDs */
typedef int GamepadButton; /**< Gamepad buttons */
typedef int GamepadAxis; /**< Gamepad axes */

#define RELEASE (State)0
#define PRESS (State)1
#define REPEAT (State)2

#define HAT_CENTERED           (Hat)0
#define HAT_UP                 (Hat)1
#define HAT_RIGHT              (Hat)2
#define HAT_DOWN               (Hat)4
#define HAT_LEFT               (Hat)8
#define HAT_RIGHT_UP           (Hat)(HAT_RIGHT | HAT_UP)
#define HAT_RIGHT_DOWN         (Hat)(HAT_RIGHT | HAT_DOWN)
#define HAT_LEFT_UP            (Hat)(HAT_LEFT  | HAT_UP)
#define HAT_LEFT_DOWN          (Hat)(HAT_LEFT  | HAT_DOWN)

#define KEY_UNKNOWN            (Key)-1

#define KEY_SPACE              (Key)32
#define KEY_APOSTROPHE         (Key)39  /* ' */
#define KEY_COMMA              (Key)44  /* , */
#define KEY_MINUS              (Key)45  /* - */
#define KEY_PERIOD             (Key)46  /* . */
#define KEY_SLASH              (Key)47  /* / */
#define KEY_0                  (Key)48
#define KEY_1                  (Key)49
#define KEY_2                  (Key)50
#define KEY_3                  (Key)51
#define KEY_4                  (Key)52
#define KEY_5                  (Key)53
#define KEY_6                  (Key)54
#define KEY_7                  (Key)55
#define KEY_8                  (Key)56
#define KEY_9                  (Key)57
#define KEY_SEMICOLON          (Key)59  /* ; */
#define KEY_EQUAL              (Key)61  /* = */
#define KEY_A                  (Key)65
#define KEY_B                  (Key)66
#define KEY_C                  (Key)67
#define KEY_D                  (Key)68
#define KEY_E                  (Key)69
#define KEY_F                  (Key)70
#define KEY_G                  (Key)71
#define KEY_H                  (Key)72
#define KEY_I                  (Key)73
#define KEY_J                  (Key)74
#define KEY_K                  (Key)75
#define KEY_L                  (Key)76
#define KEY_M                  (Key)77
#define KEY_N                  (Key)78
#define KEY_O                  (Key)79
#define KEY_P                  (Key)80
#define KEY_Q                  (Key)81
#define KEY_R                  (Key)82
#define KEY_S                  (Key)83
#define KEY_T                  (Key)84
#define KEY_U                  (Key)85
#define KEY_V                  (Key)86
#define KEY_W                  (Key)87
#define KEY_X                  (Key)88
#define KEY_Y                  (Key)89
#define KEY_Z                  (Key)90
#define KEY_LEFT_BRACKET       (Key)91  /* [ */
#define KEY_BACKSLASH          (Key)92  /* \ */
#define KEY_RIGHT_BRACKET      (Key)93  /* ] */
#define KEY_GRAVE_ACCENT       (Key)96  /* ` */
#define KEY_WORLD_1            (Key)161 /* non-US #1 */
#define KEY_WORLD_2            (Key)162 /* non-US #2 */

#define KEY_ESCAPE             (Key)256
#define KEY_ENTER              (Key)257
#define KEY_TAB                (Key)258
#define KEY_BACKSPACE          (Key)259
#define KEY_INSERT             (Key)260
#define KEY_DELETE             (Key)261
#define KEY_RIGHT              (Key)262
#define KEY_LEFT               (Key)263
#define KEY_DOWN               (Key)264
#define KEY_UP                 (Key)265
#define KEY_PAGE_UP            (Key)266
#define KEY_PAGE_DOWN          (Key)267
#define KEY_HOME               (Key)268
#define KEY_END                (Key)269
#define KEY_CAPS_LOCK          (Key)280
#define KEY_SCROLL_LOCK        (Key)281
#define KEY_NUM_LOCK           (Key)282
#define KEY_PRINT_SCREEN       (Key)283
#define KEY_PAUSE              (Key)284
#define KEY_F1                 (Key)290
#define KEY_F2                 (Key)291
#define KEY_F3                 (Key)292
#define KEY_F4                 (Key)293
#define KEY_F5                 (Key)294
#define KEY_F6                 (Key)295
#define KEY_F7                 (Key)296
#define KEY_F8                 (Key)297
#define KEY_F9                 (Key)298
#define KEY_F10                (Key)299
#define KEY_F11                (Key)300
#define KEY_F12                (Key)301
#define KEY_F13                (Key)302
#define KEY_F14                (Key)303
#define KEY_F15                (Key)304
#define KEY_F16                (Key)305
#define KEY_F17                (Key)306
#define KEY_F18                (Key)307
#define KEY_F19                (Key)308
#define KEY_F20                (Key)309
#define KEY_F21                (Key)310
#define KEY_F22                (Key)311
#define KEY_F23                (Key)312
#define KEY_F24                (Key)313
#define KEY_F25                (Key)314
#define KEY_KP_0               (Key)320
#define KEY_KP_1               (Key)321
#define KEY_KP_2               (Key)322
#define KEY_KP_3               (Key)323
#define KEY_KP_4               (Key)324
#define KEY_KP_5               (Key)325
#define KEY_KP_6               (Key)326
#define KEY_KP_7               (Key)327
#define KEY_KP_8               (Key)328
#define KEY_KP_9               (Key)329
#define KEY_KP_DECIMAL         (Key)330
#define KEY_KP_DIVIDE          (Key)331
#define KEY_KP_MULTIPLY        (Key)332
#define KEY_KP_SUBTRACT        (Key)333
#define KEY_KP_ADD             (Key)334
#define KEY_KP_ENTER           (Key)335
#define KEY_KP_EQUAL           (Key)336
#define KEY_LEFT_SHIFT         (Key)340
#define KEY_LEFT_CONTROL       (Key)341
#define KEY_LEFT_ALT           (Key)342
#define KEY_LEFT_SUPER         (Key)343
#define KEY_RIGHT_SHIFT        (Key)344
#define KEY_RIGHT_CONTROL      (Key)345
#define KEY_RIGHT_ALT          (Key)346
#define KEY_RIGHT_SUPER        (Key)347
#define KEY_MENU               (Key)348

#define KEY_LAST               (Key)KEY_MENU

#define MOD_SHIFT           (Mod)0x0001
#define MOD_CONTROL         (Mod)0x0002
#define MOD_ALT             (Mod)0x0004
#define MOD_SUPER           (Mod)0x0008
#define MOD_CAPS_LOCK       (Mod)0x0010
#define MOD_NUM_LOCK        (Mod)0x0020

#define MOUSE_BUTTON_1         (MouseButton)0
#define MOUSE_BUTTON_2         (MouseButton)1
#define MOUSE_BUTTON_3         (MouseButton)2
#define MOUSE_BUTTON_4         (MouseButton)3
#define MOUSE_BUTTON_5         (MouseButton)4
#define MOUSE_BUTTON_6         (MouseButton)5
#define MOUSE_BUTTON_7         (MouseButton)6
#define MOUSE_BUTTON_8         (MouseButton)7
#define MOUSE_BUTTON_LAST      (MouseButton)MOUSE_BUTTON_8
#define MOUSE_BUTTON_LEFT      (MouseButton)MOUSE_BUTTON_1
#define MOUSE_BUTTON_RIGHT     (MouseButton)MOUSE_BUTTON_2
#define MOUSE_BUTTON_MIDDLE    (MouseButton)MOUSE_BUTTON_3

#define JOYSTICK_1             (Joystick)0
#define JOYSTICK_2             (Joystick)1
#define JOYSTICK_3             (Joystick)2
#define JOYSTICK_4             (Joystick)3
#define JOYSTICK_5             (Joystick)4
#define JOYSTICK_6             (Joystick)5
#define JOYSTICK_7             (Joystick)6
#define JOYSTICK_8             (Joystick)7
#define JOYSTICK_9             (Joystick)8
#define JOYSTICK_10            (Joystick)9
#define JOYSTICK_11            (Joystick)10
#define JOYSTICK_12            (Joystick)11
#define JOYSTICK_13            (Joystick)12
#define JOYSTICK_14            (Joystick)13
#define JOYSTICK_15            (Joystick)14
#define JOYSTICK_16            (Joystick)15
#define JOYSTICK_LAST          (Joystick)JOYSTICK_16

#define GAMEPAD_BUTTON_A               (GamepadButton)0
#define GAMEPAD_BUTTON_B               (GamepadButton)1
#define GAMEPAD_BUTTON_X               (GamepadButton)2
#define GAMEPAD_BUTTON_Y               (GamepadButton)3
#define GAMEPAD_BUTTON_LEFT_BUMPER     (GamepadButton)4
#define GAMEPAD_BUTTON_RIGHT_BUMPER    (GamepadButton)5
#define GAMEPAD_BUTTON_BACK            (GamepadButton)6
#define GAMEPAD_BUTTON_START           (GamepadButton)7
#define GAMEPAD_BUTTON_GUIDE           (GamepadButton)8
#define GAMEPAD_BUTTON_LEFT_THUMB      (GamepadButton)9
#define GAMEPAD_BUTTON_RIGHT_THUMB     (GamepadButton)10
#define GAMEPAD_BUTTON_DPAD_UP         (GamepadButton)11
#define GAMEPAD_BUTTON_DPAD_RIGHT      (GamepadButton)12
#define GAMEPAD_BUTTON_DPAD_DOWN       (GamepadButton)13
#define GAMEPAD_BUTTON_DPAD_LEFT       (GamepadButton)14
#define GAMEPAD_BUTTON_LAST            (GamepadButton)GAMEPAD_BUTTON_DPAD_LEFT

#define GAMEPAD_BUTTON_CROSS       (GamepadButton)GAMEPAD_BUTTON_A
#define GAMEPAD_BUTTON_CIRCLE      (GamepadButton)GAMEPAD_BUTTON_B
#define GAMEPAD_BUTTON_SQUARE      (GamepadButton)GAMEPAD_BUTTON_X
#define GAMEPAD_BUTTON_TRIANGLE    (GamepadButton)GAMEPAD_BUTTON_Y

#define GAMEPAD_AXIS_LEFT_X        (GamepadAxis)0
#define GAMEPAD_AXIS_LEFT_Y        (GamepadAxis)1
#define GAMEPAD_AXIS_RIGHT_X       (GamepadAxis)2
#define GAMEPAD_AXIS_RIGHT_Y       (GamepadAxis)3
#define GAMEPAD_AXIS_LEFT_TRIGGER  (GamepadAxis)4
#define GAMEPAD_AXIS_RIGHT_TRIGGER (GamepadAxis)5
#define GAMEPAD_AXIS_LAST          (GamepadAxis)GAMEPAD_AXIS_RIGHT_TRIGGER