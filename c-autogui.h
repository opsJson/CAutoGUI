#ifndef C_AUTOGUI_H
#define C_AUTOGUI_H

#include <windows.h>

static int counter(wchar_t* str) {
	int i = 0;
	while (*str) {
		if (*str == ',') i++;	
		str++;
	}
	return i+1;
}

typedef enum MOUSEBUTTONS {
	MBS_LEFT,
	MBS_RIGHT,
	MBS_MIDDLE
} MouseButtons;

typedef enum KEYS {
	F1 = 0x70, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	K0 = 0x30, K1, K2, K3, K4, K5, K6, K7, K8, K9,
	A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	NUMPAD0 = 0X60, NUMPAD1, NUMPAD2, NUMPAD3, NUMPAD4, NUMPAD5, NUMPAD6,
	NUMPAD7, NUMPAD8, NUMPAD9,
	
	SPACE = 0X20,  END = 0X23, HOME, LEFT, UP, RIGHT, DOWN,
	LSHIFT = 0XA0, RSHIFT, LCTRL, RCTRL, LALT, RALT,
	LWIN = 0X5B, RWIN, MENU,
	
	PAGEUP = 0x21, PAGEDOWN,
	INSERT = 0x2D, DEL,
	
	TAB = 0x09, ESC = 0x1B, ENTER = 0x0D, BACKSPACE = 0x08,
	PRINTSCREEN = 0x2A, SCROLLLOCK = 0x91, PAUSE = 0x13
} Keys;

POINT size();
POINT position();
int onScreen(int x, int y);

void move(int x, int y);
void moveTo(int x, int y);
void scroll(int s);
void click();
void rightClick();
void mouseDown(MouseButtons button);
void mouseUp(MouseButtons button);
void drag(int x, int y, MouseButtons button);
void dragTo(int x, int y, MouseButtons button);

void write(wchar_t *str);
void writeEach(wchar_t* str, int time);
void keyDown(Keys key);
void keyUp(Keys key);
void press(Keys key);
void _hotkey(size_t count, ...);
#define hotkey(...) _hotkey(counter(L###__VA_ARGS__), __VA_ARGS__)

#endif //C_AUTOGUI_H
