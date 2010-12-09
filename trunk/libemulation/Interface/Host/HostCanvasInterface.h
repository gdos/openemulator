
/**
 * libemulation
 * Host interface
 * (C) 2010 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Defines the host interface
 */

#ifndef _HOSTCANVASINTERFACE_H
#define _HOSTCANVASINTERFACE_H

// Notes
// * A component should first request a canvas from the canvas controller.
//   Then it should subscribe to canvas events.
// * Axes are in [-1.0 .. 1.0] coordinates.

typedef enum
{
	HOST_CANVAS_SET_CAPTUREMODE,
	HOST_CANVAS_SET_WINDOWFRAME,
	HOST_CANVAS_GET_WINDOWFRAME,
	HOST_CANVAS_SET_DEFAULTWINDOWSIZE,
	HOST_CANVAS_GET_VIDEOFRAME,
	HOST_CANVAS_POST_VIDEOFRAME,
	HOST_CANVAS_LOCK_OPENGL_CONTEXT,
	HOST_CANVAS_UNLOCK_OPENGL_CONTEXT,
	HOST_CANVAS_SET_KEYBOARDFLAGS,
	HOST_CANVAS_SET_BADGEFLAGS,
} HostCanvasMessages;

typedef enum
{
	HOST_CANVAS_COPY,
	HOST_CANVAS_PASTE,
} HostCanvasDelegations;

typedef enum
{
	HOST_CANVAS_SYSTEMKEYBOARD_DID_CHANGE,
	HOST_CANVAS_KEYBOARD_DID_CHANGE,
	HOST_CANVAS_UNICODEKEYBOARD_DID_CHANGE,
	HOST_CANVAS_POINTER_DID_CHANGE,
	HOST_CANVAS_MOUSE_DID_CHANGE,
	HOST_CANVAS_JOYSTICK1_DID_CHANGE,
	HOST_CANVAS_JOYSTICK2_DID_CHANGE,
	HOST_CANVAS_JOYSTICK3_DID_CHANGE,
	HOST_CANVAS_JOYSTICK4_DID_CHANGE,
} HostCanvasNotifications;

//
// HOST_CANVAS_SET_CAPTUREMODE uses int
//
typedef enum
{
	HOST_CANVAS_CAPTURE_NONE,
	HOST_CANVAS_CAPTURE_KEYBOARDANDMOUSE,
	HOST_CANVAS_CAPTURE_KEYBOARD,
} HostCanvasCaptureModes;

//
// SET_WINDOWFRAME and GET_WINDOWFRAME use an STL string in the format:
// [originX] [originY] [width] [height] [visible]
// The coordinate system's origin is lower left
// [visible] is "0" or "1"
//
// SET_DEFAULTWINDOWSIZE uses an STL string in the format:
// [width] [height]
//
typedef enum
{
	HOST_CANVAS_FRAME_FORMAT_COMPOSITE,
	HOST_CANVAS_FRAME_FORMAT_RGB,
} HostCanvasVideoFrameFormat;

typedef struct
{
	HostCanvasVideoFrameFormat frameFormat;
	void *frameData;
	int frameWidth;
	int frameHeight;
	bool compositeColorBurst;
	bool copmositeColorSubcarrier;
	bool compositeInterlaced;
	float videoHorizBegin;
	float videoHorizEnd;
	float videoVertBegin;
	float videoVertEnd;
	
	float compositeLumaCutoff;
	float compositeChromaCutoff;
	float compositeHue;
	float compositeSaturation;
	bool compositeColorize;
	float *compositeDecoderMatrix;
	float rgbSharpness;
	float screenBrightness;
	float screenContrast;
	float screenRedGain;
	float screenGreenGain;
	float screenBlueGain;
	float screenBarrel;
	float screenPersistance;
} HostCanvasVideoFrame;

// Canvas keyboard flags use int
#define HOST_CANVAS_L_NUMLOCK		(1 << 0)
#define HOST_CANVAS_L_CAPSLOCK		(1 << 1)
#define HOST_CANVAS_L_SCROLLLOCK	(1 << 2)
#define HOST_CANVAS_L_COMPOSE		(1 << 3)
#define HOST_CANVAS_L_KANA			(1 << 4)
#define HOST_CANVAS_L_POWER			(1 << 5)
#define HOST_CANVAS_L_SHIFT			(1 << 6)

// Canvas badge flags use int
#define HOST_CANVAS_B_POWER			(1 << 0)
#define HOST_CANVAS_B_PAUSE			(1 << 1)

// Copy and paste use an STL string

// Canvas human-interface device notifications use this structure
typedef struct
{
	int usageId;
	float value;
} HostCanvasHIDNotification;

// Canvas human-interface device definitions follow
#define HOST_CANVAS_KEYBOARD_KEY_NUM	256
#define HOST_CANVAS_POINTER_BUTTON_NUM	8
#define HOST_CANVAS_MOUSE_BUTTON_NUM	8
#define HOST_CANVAS_JOYSTICK_NUM		4
#define HOST_CANVAS_JOYSTICK_AXIS_NUM	16
#define HOST_CANVAS_JOYSTICK_BUTTON_NUM	16
#define HOST_CANVAS_JOYSTICK_HAT_NUM	4
#define HOST_CANVAS_JOYSTICK_RAXIS_NUM	4

typedef enum
{
	HOST_CANVAS_S_POWERDOWN = 0x81,
	HOST_CANVAS_S_SLEEP,
	HOST_CANVAS_S_WAKEUP,
	HOST_CANVAS_S_CONTEXT,
	HOST_CANVAS_S_MAINMENU,
	HOST_CANVAS_S_APPMENU,
	HOST_CANVAS_S_MENUHELP,
	HOST_CANVAS_S_MENUEXIT,
	HOST_CANVAS_S_MENUSELECT,
	HOST_CANVAS_S_MENURIGHT,
	HOST_CANVAS_S_MENULEFT,
	HOST_CANVAS_S_MENUUP,
	HOST_CANVAS_S_MENUDOWN,
	HOST_CANVAS_S_COLDRESTART,
	HOST_CANVAS_S_WARMRESTART,
	HOST_CANVAS_S_DPADUP,
	HOST_CANVAS_S_DPADDOWN,
	HOST_CANVAS_S_DPADRIGHT,
	HOST_CANVAS_S_DPADLEFT,
	
	HOST_CANVAS_S_DOCK = 0xa0,
	HOST_CANVAS_S_UNDOCK,
	HOST_CANVAS_S_SETUP,
	HOST_CANVAS_S_BREAK,
	HOST_CANVAS_S_DEBUGGERBREAK,
	HOST_CANVAS_S_APPLICATIONBREAK,
	HOST_CANVAS_S_APPLICATIONDEBUGGERBREAK,
	HOST_CANVAS_S_SPEAKERMUTE,
	HOST_CANVAS_S_HIBERNATE,
	
	HOST_CANVAS_S_DISPLAYINVERT = 0xb0,
	HOST_CANVAS_S_DISPLAYINTERNAL,
	HOST_CANVAS_S_DISPLAYEXTERNAL,
	HOST_CANVAS_S_DISPLAYBOTH,
	HOST_CANVAS_S_DISPLAYDUAL,
	HOST_CANVAS_S_DISPLAYTOGGLEINTEXT,
	HOST_CANVAS_S_DISPLAYSWAPPRIMARYSECONDARY,
	HOST_CANVAS_S_DISPLAYLCDAUTOSCALE,
} HostCanvasSystemUsageIds;

typedef enum {
	HOST_CANVAS_K_A = 0x04,
	HOST_CANVAS_K_B,
	HOST_CANVAS_K_C,
	HOST_CANVAS_K_D,
	HOST_CANVAS_K_E,
	HOST_CANVAS_K_F,
	HOST_CANVAS_K_G,
	HOST_CANVAS_K_H,
	HOST_CANVAS_K_I,
	HOST_CANVAS_K_J,
	HOST_CANVAS_K_K,
	HOST_CANVAS_K_L,
	HOST_CANVAS_K_M,
	HOST_CANVAS_K_N,
	HOST_CANVAS_K_O,
	HOST_CANVAS_K_P,
	HOST_CANVAS_K_Q,
	HOST_CANVAS_K_R,
	HOST_CANVAS_K_S,
	HOST_CANVAS_K_T,
	HOST_CANVAS_K_U,
	HOST_CANVAS_K_V,
	HOST_CANVAS_K_W,
	HOST_CANVAS_K_X,
	HOST_CANVAS_K_Y,
	HOST_CANVAS_K_Z,
	HOST_CANVAS_K_1,
	HOST_CANVAS_K_2,
	HOST_CANVAS_K_3,
	HOST_CANVAS_K_4,
	HOST_CANVAS_K_5,
	HOST_CANVAS_K_6,
	HOST_CANVAS_K_7,
	HOST_CANVAS_K_8,
	HOST_CANVAS_K_9,
	HOST_CANVAS_K_0,
	HOST_CANVAS_K_ENTER,
	HOST_CANVAS_K_ESCAPE,
	HOST_CANVAS_K_BACKSPACE,
	HOST_CANVAS_K_TAB,
	HOST_CANVAS_K_SPACE,
	HOST_CANVAS_K_MINUS,
	HOST_CANVAS_K_EQUAL,
	HOST_CANVAS_K_LEFTBRACKET,
	HOST_CANVAS_K_RIGHTBRACKET,
	HOST_CANVAS_K_BACKSLASH,
	HOST_CANVAS_K_NON_US1,
	HOST_CANVAS_K_SEMICOLON,
	HOST_CANVAS_K_QUOTE,
	HOST_CANVAS_K_GRAVEACCENT,
	HOST_CANVAS_K_COMMA,
	HOST_CANVAS_K_PERIOD,
	HOST_CANVAS_K_SLASH,
	HOST_CANVAS_K_CAPSLOCK,
	HOST_CANVAS_K_F1,
	HOST_CANVAS_K_F2,
	HOST_CANVAS_K_F3,
	HOST_CANVAS_K_F4,
	HOST_CANVAS_K_F5,
	HOST_CANVAS_K_F6,
	HOST_CANVAS_K_F7,
	HOST_CANVAS_K_F8,
	HOST_CANVAS_K_F9,
	HOST_CANVAS_K_F10,
	HOST_CANVAS_K_F11,
	HOST_CANVAS_K_F12,
	HOST_CANVAS_K_PRINTSCREEN,
	HOST_CANVAS_K_SCROLLLOCK,
	HOST_CANVAS_K_PAUSE,
	HOST_CANVAS_K_INSERT,
	HOST_CANVAS_K_HOME,
	HOST_CANVAS_K_PAGEUP,
	HOST_CANVAS_K_DELETE,
	HOST_CANVAS_K_END,
	HOST_CANVAS_K_PAGEDOWN,
	HOST_CANVAS_K_RIGHT,
	HOST_CANVAS_K_LEFT,
	HOST_CANVAS_K_DOWN,
	HOST_CANVAS_K_UP,
	HOST_CANVAS_KP_NUMLOCK,
	HOST_CANVAS_KP_SLASH,
	HOST_CANVAS_KP_STAR,
	HOST_CANVAS_KP_MINUS,
	HOST_CANVAS_KP_PLUS,
	HOST_CANVAS_KP_ENTER,
	HOST_CANVAS_KP_1,
	HOST_CANVAS_KP_2,
	HOST_CANVAS_KP_3,
	HOST_CANVAS_KP_4,
	HOST_CANVAS_KP_5,
	HOST_CANVAS_KP_6,
	HOST_CANVAS_KP_7,
	HOST_CANVAS_KP_8,
	HOST_CANVAS_KP_9,
	HOST_CANVAS_KP_0,
	HOST_CANVAS_KP_PERIOD,
	HOST_CANVAS_K_NON_US2,
	HOST_CANVAS_K_APPLICATION,
	HOST_CANVAS_K_POWER,
	HOST_CANVAS_KP_EQUAL,
	HOST_CANVAS_K_F13,
	HOST_CANVAS_K_F14,
	HOST_CANVAS_K_F15,
	HOST_CANVAS_K_F16,
	HOST_CANVAS_K_F17,
	HOST_CANVAS_K_F18,
	HOST_CANVAS_K_F19,
	HOST_CANVAS_K_F20,
	HOST_CANVAS_K_F21,
	HOST_CANVAS_K_F22,
	HOST_CANVAS_K_F23,
	HOST_CANVAS_K_F24,
	HOST_CANVAS_K_EXECUTE,
	HOST_CANVAS_K_HELP,
	HOST_CANVAS_K_MENU,
	HOST_CANVAS_K_SELECT,
	HOST_CANVAS_K_STOP,
	HOST_CANVAS_K_AGAIN,
	HOST_CANVAS_K_UNDO,
	HOST_CANVAS_K_CUT,
	HOST_CANVAS_K_COPY,
	HOST_CANVAS_K_PASTE,
	HOST_CANVAS_K_FIND,
	HOST_CANVAS_K_MUTE,
	HOST_CANVAS_K_VOLUMEUP,
	HOST_CANVAS_K_VOLUMEDOWN,
	HOST_CANVAS_K_LOCKINGCAPSLOCK,
	HOST_CANVAS_K_LOCKINGNUMLOCK,
	HOST_CANVAS_K_LOCKINGSCROLLLOCK,
	HOST_CANVAS_KP_COMMA,
	HOST_CANVAS_KP_EQUAL2,
	HOST_CANVAS_K_INTERNATIONAL1,
	HOST_CANVAS_K_INTERNATIONAL2,
	HOST_CANVAS_K_INTERNATIONAL3,
	HOST_CANVAS_K_INTERNATIONAL4,
	HOST_CANVAS_K_INTERNATIONAL5,
	HOST_CANVAS_K_INTERNATIONAL6,
	HOST_CANVAS_K_INTERNATIONAL7,
	HOST_CANVAS_K_INTERNATIONAL8,
	HOST_CANVAS_K_INTERNATIONAL9,
	HOST_CANVAS_K_LANG1,
	HOST_CANVAS_K_LANG2,
	HOST_CANVAS_K_LANG3,
	HOST_CANVAS_K_LANG4,
	HOST_CANVAS_K_LANG5,
	HOST_CANVAS_K_LANG6,
	HOST_CANVAS_K_LANG7,
	HOST_CANVAS_K_LANG8,
	HOST_CANVAS_K_LANG9,
	HOST_CANVAS_K_ALTERASE,
	HOST_CANVAS_K_SYSREQ,
	HOST_CANVAS_K_CANCEL,
	HOST_CANVAS_K_CLEAR,
	HOST_CANVAS_K_PRIOR,
	HOST_CANVAS_K_RETURN,
	HOST_CANVAS_K_SEPARATOR,
	HOST_CANVAS_K_OUT,
	HOST_CANVAS_K_OPER,
	HOST_CANVAS_K_CLEARAGAIN,
	HOST_CANVAS_K_CRSELPROPS,
	HOST_CANVAS_K_EXSEL,
	
	HOST_CANVAS_KP_00 = 0xb0,
	HOST_CANVAS_KP_000,
	HOST_CANVAS_KP_THOUSANDSSEPARATOR,
	HOST_CANVAS_KP_DECIMALSEPARATOR,
	HOST_CANVAS_KP_CURRENCYUNIT,
	HOST_CANVAS_KP_CURRENCYSUBUNIT,
	HOST_CANVAS_KP_LEFTPARENTHESIS,
	HOST_CANVAS_KP_RIGHTPARENTHESIS,
	HOST_CANVAS_KP_LEFTCURLYBRACKET,
	HOST_CANVAS_KP_RIGHTCURLYBRACKET,
	HOST_CANVAS_KP_TAB,
	HOST_CANVAS_KP_BACKSPACE,
	HOST_CANVAS_KP_A,
	HOST_CANVAS_KP_B,
	HOST_CANVAS_KP_C,
	HOST_CANVAS_KP_D,
	HOST_CANVAS_KP_E,
	HOST_CANVAS_KP_F,
	HOST_CANVAS_KP_XOR,
	HOST_CANVAS_KP_CARET,
	HOST_CANVAS_KP_PERCENT,
	HOST_CANVAS_KP_LESS,
	HOST_CANVAS_KP_MORE,
	HOST_CANVAS_KP_AND,
	HOST_CANVAS_KP_LOGICAND,
	HOST_CANVAS_KP_OR,
	HOST_CANVAS_KP_LOGICOR,
	HOST_CANVAS_KP_COLON,
	HOST_CANVAS_KP_NUMERAL,
	HOST_CANVAS_KP_SPACE,
	HOST_CANVAS_KP_AT,
	HOST_CANVAS_KP_EXCLAMATION,
	HOST_CANVAS_KP_MEMSTORE,
	HOST_CANVAS_KP_MEMRECALL,
	HOST_CANVAS_KP_MEMCLEAR,
	HOST_CANVAS_KP_MEMADD,
	HOST_CANVAS_KP_MEMSUBTRACT,
	HOST_CANVAS_KP_MEMMULTIPLY,
	HOST_CANVAS_KP_MEMDIVIDE,
	HOST_CANVAS_KP_PLUSMINUS,
	HOST_CANVAS_KP_CLEAR,
	HOST_CANVAS_KP_CLEARENTRY,
	HOST_CANVAS_KP_BINARY,
	HOST_CANVAS_KP_OCTAL,
	HOST_CANVAS_KP_DECIMAL,
	HOST_CANVAS_KP_HEXADECIMAL,
	
	HOST_CANVAS_K_LEFTCONTROL = 0xe0,
	HOST_CANVAS_K_LEFTSHIFT,
	HOST_CANVAS_K_LEFTALT,
	HOST_CANVAS_K_LEFTGUI,
	HOST_CANVAS_K_RIGHTCONTROL,
	HOST_CANVAS_K_RIGHTSHIFT,
	HOST_CANVAS_K_RIGHTALT,
	HOST_CANVAS_K_RIGHTGUI,
} HostCanvasKeyboardUsageIds;

typedef enum
{
	HOST_CANVAS_P_X,
	HOST_CANVAS_P_Y,
	HOST_CANVAS_P_BUTTON1,
	HOST_CANVAS_P_BUTTON2,
	HOST_CANVAS_P_BUTTON3,
	HOST_CANVAS_P_BUTTON4,
	HOST_CANVAS_P_BUTTON5,
	HOST_CANVAS_P_BUTTON6,
	HOST_CANVAS_P_BUTTON7,
	HOST_CANVAS_P_BUTTON8,
	HOST_CANVAS_P_WHEELX,
	HOST_CANVAS_P_WHEELY,
} HostCanvasPointerUsageIds;

typedef enum
{
	HOST_CANVAS_M_RELX,
	HOST_CANVAS_M_RELY,
	HOST_CANVAS_M_BUTTON1,
	HOST_CANVAS_M_BUTTON2,
	HOST_CANVAS_M_BUTTON3,
	HOST_CANVAS_M_BUTTON4,
	HOST_CANVAS_M_BUTTON5,
	HOST_CANVAS_M_BUTTON6,
	HOST_CANVAS_M_BUTTON7,
	HOST_CANVAS_M_BUTTON8,
	HOST_CANVAS_M_WHEELX,
	HOST_CANVAS_M_WHEELY,
} HostCanvasMouseUsageIds;

typedef enum
{
	HOST_CANVAS_J_AXIS1,
	HOST_CANVAS_J_AXIS2,
	HOST_CANVAS_J_AXIS3,
	HOST_CANVAS_J_AXIS4,
	HOST_CANVAS_J_AXIS5,
	HOST_CANVAS_J_AXIS6,
	HOST_CANVAS_J_AXIS7,
	HOST_CANVAS_J_AXIS8,
	HOST_CANVAS_J_AXIS9,
	HOST_CANVAS_J_AXIS10,
	HOST_CANVAS_J_AXIS11,
	HOST_CANVAS_J_AXIS12,
	HOST_CANVAS_J_AXIS13,
	HOST_CANVAS_J_AXIS14,
	HOST_CANVAS_J_AXIS15,
	HOST_CANVAS_J_AXIS16,
	HOST_CANVAS_J_BUTTON1,
	HOST_CANVAS_J_BUTTON2,
	HOST_CANVAS_J_BUTTON3,
	HOST_CANVAS_J_BUTTON4,
	HOST_CANVAS_J_BUTTON5,
	HOST_CANVAS_J_BUTTON6,
	HOST_CANVAS_J_BUTTON7,
	HOST_CANVAS_J_BUTTON8,
	HOST_CANVAS_J_BUTTON9,
	HOST_CANVAS_J_BUTTON10,
	HOST_CANVAS_J_BUTTON11,
	HOST_CANVAS_J_BUTTON12,
	HOST_CANVAS_J_BUTTON13,
	HOST_CANVAS_J_BUTTON14,
	HOST_CANVAS_J_BUTTON15,
	HOST_CANVAS_J_BUTTON16,
	HOST_CANVAS_J_HAT1,
	HOST_CANVAS_J_HAT2,
	HOST_CANVAS_J_HAT3,
	HOST_CANVAS_J_HAT4,
	HOST_CANVAS_J_RELAXIS1,
	HOST_CANVAS_J_RELAXIS2,
	HOST_CANVAS_J_RELAXIS3,
	HOST_CANVAS_J_RELAXIS4,
} HostCanvasJoystickUsageIds;

#endif
