#pragma once
#include "Common.h"

#include "Debug.h"

#include <glm/glm.hpp>

#include <glad/glad.h> // TODO: Make this renderer-dependent
#include <GLFW/glfw3.h>

namespace Kiwi {

	class Window
	{
	public:
		Window(std::string_view title, uint32_t width, uint32_t height);
		~Window();

	public:
		bool ShouldClose();

		void FrameBegin();

		void Present();

		void BecomeCurrent();

		GLFWwindow* GetGLFWWindow();

		uint32_t GetWidth();

		uint32_t GetHeight();

		double GetDeltaTime();

	private:
		GLFWwindow* m_Window = nullptr;

		double m_Delta = 0;
		double m_StartTime = 0;
		double m_EndTime = 0;
	};

	inline Window* g_CurrentWindow;

	namespace Input {

		bool IsKeyPressed(uint32_t key);

		bool IsMouseButtonPressed(uint32_t button);

		glm::vec2 GetMousePosition();

	}

}

#define KIWI_HAT_CENTERED           0
#define KIWI_HAT_UP                 1
#define KIWI_HAT_RIGHT              2
#define KIWI_HAT_DOWN               4
#define KIWI_HAT_LEFT               8
#define KIWI_HAT_RIGHT_UP           (KIWI_HAT_RIGHT | KIWI_HAT_UP)
#define KIWI_HAT_RIGHT_DOWN         (KIWI_HAT_RIGHT | KIWI_HAT_DOWN)
#define KIWI_HAT_LEFT_UP            (KIWI_HAT_LEFT  | KIWI_HAT_UP)
#define KIWI_HAT_LEFT_DOWN          (KIWI_HAT_LEFT  | KIWI_HAT_DOWN)

/*! @ingroup input
 */
#define KIWI_KEY_UNKNOWN            -1

 /*! @} */

 /*! @defgroup keys Keyboard key tokens
  *  @brief Keyboard key tokens.
  *
  *  See [key input](@ref input_key) for how these are used.
  *
  *  These key codes are inspired by the _USB HID Usage Tables v1.12_ (p. 53-60),
  *  but re-arranged to map to 7-bit ASCII for printable keys (function keys are
  *  put in the 256+ range).
  *
  *  The naming of the key codes follow these rules:
  *   - The US keyboard layout is used
  *   - Names of printable alphanumeric characters are used (e.g. "A", "R",
  *     "3", etc.)
  *   - For non-alphanumeric characters, Unicode:ish names are used (e.g.
  *     "COMMA", "LEFT_SQUARE_BRACKET", etc.). Note that some names do not
  *     correspond to the Unicode standard (usually for brevity)
  *   - Keys that lack a clear US mapping are named "WORLD_x"
  *   - For non-printable keys, custom names are used (e.g. "F4",
  *     "BACKSPACE", etc.)
  *
  *  @ingroup input
  *  @{
  */

  /* Printable keys */
#define KIWI_KEY_SPACE              32
#define KIWI_KEY_APOSTROPHE         39  /* ' */
#define KIWI_KEY_COMMA              44  /* , */
#define KIWI_KEY_MINUS              45  /* - */
#define KIWI_KEY_PERIOD             46  /* . */
#define KIWI_KEY_SLASH              47  /* / */
#define KIWI_KEY_0                  48
#define KIWI_KEY_1                  49
#define KIWI_KEY_2                  50
#define KIWI_KEY_3                  51
#define KIWI_KEY_4                  52
#define KIWI_KEY_5                  53
#define KIWI_KEY_6                  54
#define KIWI_KEY_7                  55
#define KIWI_KEY_8                  56
#define KIWI_KEY_9                  57
#define KIWI_KEY_SEMICOLON          59  /* ; */
#define KIWI_KEY_EQUAL              61  /* = */
#define KIWI_KEY_A                  65
#define KIWI_KEY_B                  66
#define KIWI_KEY_C                  67
#define KIWI_KEY_D                  68
#define KIWI_KEY_E                  69
#define KIWI_KEY_F                  70
#define KIWI_KEY_G                  71
#define KIWI_KEY_H                  72
#define KIWI_KEY_I                  73
#define KIWI_KEY_J                  74
#define KIWI_KEY_K                  75
#define KIWI_KEY_L                  76
#define KIWI_KEY_M                  77
#define KIWI_KEY_N                  78
#define KIWI_KEY_O                  79
#define KIWI_KEY_P                  80
#define KIWI_KEY_Q                  81
#define KIWI_KEY_R                  82
#define KIWI_KEY_S                  83
#define KIWI_KEY_T                  84
#define KIWI_KEY_U                  85
#define KIWI_KEY_V                  86
#define KIWI_KEY_W                  87
#define KIWI_KEY_X                  88
#define KIWI_KEY_Y                  89
#define KIWI_KEY_Z                  90
#define KIWI_KEY_LEFT_BRACKET       91  /* [ */
#define KIWI_KEY_BACKSLASH          92  /* \ */
#define KIWI_KEY_RIGHT_BRACKET      93  /* ] */
#define KIWI_KEY_GRAVE_ACCENT       96  /* ` */
#define KIWI_KEY_WORLD_1            161 /* non-US #1 */
#define KIWI_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define KIWI_KEY_ESCAPE             256
#define KIWI_KEY_ENTER              257
#define KIWI_KEY_TAB                258
#define KIWI_KEY_BACKSPACE          259
#define KIWI_KEY_INSERT             260
#define KIWI_KEY_DELETE             261
#define KIWI_KEY_RIGHT              262
#define KIWI_KEY_LEFT               263
#define KIWI_KEY_DOWN               264
#define KIWI_KEY_UP                 265
#define KIWI_KEY_PAGE_UP            266
#define KIWI_KEY_PAGE_DOWN          267
#define KIWI_KEY_HOME               268
#define KIWI_KEY_END                269
#define KIWI_KEY_CAPS_LOCK          280
#define KIWI_KEY_SCROLL_LOCK        281
#define KIWI_KEY_NUM_LOCK           282
#define KIWI_KEY_PRINT_SCREEN       283
#define KIWI_KEY_PAUSE              284
#define KIWI_KEY_F1                 290
#define KIWI_KEY_F2                 291
#define KIWI_KEY_F3                 292
#define KIWI_KEY_F4                 293
#define KIWI_KEY_F5                 294
#define KIWI_KEY_F6                 295
#define KIWI_KEY_F7                 296
#define KIWI_KEY_F8                 297
#define KIWI_KEY_F9                 298
#define KIWI_KEY_F10                299
#define KIWI_KEY_F11                300
#define KIWI_KEY_F12                301
#define KIWI_KEY_F13                302
#define KIWI_KEY_F14                303
#define KIWI_KEY_F15                304
#define KIWI_KEY_F16                305
#define KIWI_KEY_F17                306
#define KIWI_KEY_F18                307
#define KIWI_KEY_F19                308
#define KIWI_KEY_F20                309
#define KIWI_KEY_F21                310
#define KIWI_KEY_F22                311
#define KIWI_KEY_F23                312
#define KIWI_KEY_F24                313
#define KIWI_KEY_F25                314
#define KIWI_KEY_KP_0               320
#define KIWI_KEY_KP_1               321
#define KIWI_KEY_KP_2               322
#define KIWI_KEY_KP_3               323
#define KIWI_KEY_KP_4               324
#define KIWI_KEY_KP_5               325
#define KIWI_KEY_KP_6               326
#define KIWI_KEY_KP_7               327
#define KIWI_KEY_KP_8               328
#define KIWI_KEY_KP_9               329
#define KIWI_KEY_KP_DECIMAL         330
#define KIWI_KEY_KP_DIVIDE          331
#define KIWI_KEY_KP_MULTIPLY        332
#define KIWI_KEY_KP_SUBTRACT        333
#define KIWI_KEY_KP_ADD             334
#define KIWI_KEY_KP_ENTER           335
#define KIWI_KEY_KP_EQUAL           336
#define KIWI_KEY_LEFT_SHIFT         340
#define KIWI_KEY_LEFT_CONTROL       341
#define KIWI_KEY_LEFT_ALT           342
#define KIWI_KEY_LEFT_SUPER         343
#define KIWI_KEY_RIGHT_SHIFT        344
#define KIWI_KEY_RIGHT_CONTROL      345
#define KIWI_KEY_RIGHT_ALT          346
#define KIWI_KEY_RIGHT_SUPER        347
#define KIWI_KEY_MENU               348

#define KIWI_KEY_LAST               KIWI_KEY_MENU

/*! @} */

/*! @defgroup mods Modifier key flags
 *  @brief Modifier key flags.
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  @ingroup input
 *  @{ */

 /*! @brief If this bit is set one or more Shift keys were held down.
  *
  *  If this bit is set one or more Shift keys were held down.
  */
#define KIWI_MOD_SHIFT           0x0001
  /*! @brief If this bit is set one or more Control keys were held down.
   *
   *  If this bit is set one or more Control keys were held down.
   */
#define KIWI_MOD_CONTROL         0x0002
   /*! @brief If this bit is set one or more Alt keys were held down.
	*
	*  If this bit is set one or more Alt keys were held down.
	*/
#define KIWI_MOD_ALT             0x0004
	/*! @brief If this bit is set one or more Super keys were held down.
	 *
	 *  If this bit is set one or more Super keys were held down.
	 */
#define KIWI_MOD_SUPER           0x0008
	 /*! @brief If this bit is set the Caps Lock key is enabled.
	  *
	  *  If this bit is set the Caps Lock key is enabled and the @ref
	  *  KIWI_LOCK_KEY_MODS input mode is set.
	  */
#define KIWI_MOD_CAPS_LOCK       0x0010
	  /*! @brief If this bit is set the Num Lock key is enabled.
	   *
	   *  If this bit is set the Num Lock key is enabled and the @ref
	   *  KIWI_LOCK_KEY_MODS input mode is set.
	   */
#define KIWI_MOD_NUM_LOCK        0x0020

	   /*! @} */

	   /*! @defgroup buttons Mouse buttons
		*  @brief Mouse button IDs.
		*
		*  See [mouse button input](@ref input_mouse_button) for how these are used.
		*
		*  @ingroup input
		*  @{ */
#define KIWI_MOUSE_BUTTON_1         0
#define KIWI_MOUSE_BUTTON_2         1
#define KIWI_MOUSE_BUTTON_3         2
#define KIWI_MOUSE_BUTTON_4         3
#define KIWI_MOUSE_BUTTON_5         4
#define KIWI_MOUSE_BUTTON_6         5
#define KIWI_MOUSE_BUTTON_7         6
#define KIWI_MOUSE_BUTTON_8         7
#define KIWI_MOUSE_BUTTON_LAST      KIWI_MOUSE_BUTTON_8
#define KIWI_MOUSE_BUTTON_LEFT      KIWI_MOUSE_BUTTON_1
#define KIWI_MOUSE_BUTTON_RIGHT     KIWI_MOUSE_BUTTON_2
#define KIWI_MOUSE_BUTTON_MIDDLE    KIWI_MOUSE_BUTTON_3
		/*! @} */

		/*! @defgroup joysticks Joysticks
		 *  @brief Joystick IDs.
		 *
		 *  See [joystick input](@ref joystick) for how these are used.
		 *
		 *  @ingroup input
		 *  @{ */
#define KIWI_JOYSTICK_1             0
#define KIWI_JOYSTICK_2             1
#define KIWI_JOYSTICK_3             2
#define KIWI_JOYSTICK_4             3
#define KIWI_JOYSTICK_5             4
#define KIWI_JOYSTICK_6             5
#define KIWI_JOYSTICK_7             6
#define KIWI_JOYSTICK_8             7
#define KIWI_JOYSTICK_9             8
#define KIWI_JOYSTICK_10            9
#define KIWI_JOYSTICK_11            10
#define KIWI_JOYSTICK_12            11
#define KIWI_JOYSTICK_13            12
#define KIWI_JOYSTICK_14            13
#define KIWI_JOYSTICK_15            14
#define KIWI_JOYSTICK_16            15
#define KIWI_JOYSTICK_LAST          KIWI_JOYSTICK_16
		 /*! @} */

		 /*! @defgroup gamepad_buttons Gamepad buttons
		  *  @brief Gamepad buttons.
		  *
		  *  See @ref gamepad for how these are used.
		  *
		  *  @ingroup input
		  *  @{ */
#define KIWI_GAMEPAD_BUTTON_A               0
#define KIWI_GAMEPAD_BUTTON_B               1
#define KIWI_GAMEPAD_BUTTON_X               2
#define KIWI_GAMEPAD_BUTTON_Y               3
#define KIWI_GAMEPAD_BUTTON_LEFT_BUMPER     4
#define KIWI_GAMEPAD_BUTTON_RIGHT_BUMPER    5
#define KIWI_GAMEPAD_BUTTON_BACK            6
#define KIWI_GAMEPAD_BUTTON_START           7
#define KIWI_GAMEPAD_BUTTON_GUIDE           8
#define KIWI_GAMEPAD_BUTTON_LEFT_THUMB      9
#define KIWI_GAMEPAD_BUTTON_RIGHT_THUMB     10
#define KIWI_GAMEPAD_BUTTON_DPAD_UP         11
#define KIWI_GAMEPAD_BUTTON_DPAD_RIGHT      12
#define KIWI_GAMEPAD_BUTTON_DPAD_DOWN       13
#define KIWI_GAMEPAD_BUTTON_DPAD_LEFT       14
#define KIWI_GAMEPAD_BUTTON_LAST            KIWI_GAMEPAD_BUTTON_DPAD_LEFT

#define KIWI_GAMEPAD_BUTTON_CROSS       KIWI_GAMEPAD_BUTTON_A
#define KIWI_GAMEPAD_BUTTON_CIRCLE      KIWI_GAMEPAD_BUTTON_B
#define KIWI_GAMEPAD_BUTTON_SQUARE      KIWI_GAMEPAD_BUTTON_X
#define KIWI_GAMEPAD_BUTTON_TRIANGLE    KIWI_GAMEPAD_BUTTON_Y
		  /*! @} */

		  /*! @defgroup gamepad_axes Gamepad axes
		   *  @brief Gamepad axes.
		   *
		   *  See @ref gamepad for how these are used.
		   *
		   *  @ingroup input
		   *  @{ */
#define KIWI_GAMEPAD_AXIS_LEFT_X        0
#define KIWI_GAMEPAD_AXIS_LEFT_Y        1
#define KIWI_GAMEPAD_AXIS_RIGHT_X       2
#define KIWI_GAMEPAD_AXIS_RIGHT_Y       3
#define KIWI_GAMEPAD_AXIS_LEFT_TRIGGER  4
#define KIWI_GAMEPAD_AXIS_RIGHT_TRIGGER 5
#define KIWI_GAMEPAD_AXIS_LAST          KIWI_GAMEPAD_AXIS_RIGHT_TRIGGER
		   /*! @} */

