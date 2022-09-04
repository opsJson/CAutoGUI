#ifndef C_AUTOGUI_H
#define C_AUTOGUI_H

#include <windows.h>

enum MouseButtons {
	MBS_LEFT,
	MBS_RIGHT,
	MBS_MIDDLE
};

enum Keys {
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
};

POINT size();
POINT position();
int onScreen(int x, int y);

void move(int x, int y);
void moveTo(int x, int y);
void scroll(int s);
void click();
void rightClick();
void mouseDown(enum MouseButtons button);
void mouseUp(enum MouseButtons button);
void drag(int x, int y, enum MouseButtons button);
void dragTo(int x, int y, enum MouseButtons button);

void write(wchar_t *str);
void writeEach(wchar_t* str, int time);
void keyDown(enum Keys key);
void keyUp(enum Keys key);
void press(enum Keys key);
void hotkey(size_t count, ...);

#endif /* C_AUTOGUI_H */

#ifdef C_AUTOGUI_IMPLEMENTATION

int counter(wchar_t* str) {
	int i = 0;
	while (*str) {
		if (*str == ',') i++;	
		str++;
	}
	return i+1;
}

POINT size() {
	POINT s;
	s.x = GetSystemMetrics(SM_CXSCREEN);
	s.y = GetSystemMetrics(SM_CXSCREEN);
	
	return s;
}

POINT position() {
	POINT pos;
	GetCursorPos(&pos);
	
	return pos;
}

int onScreen(int x, int y) {
	POINT screen;
	
	if (x < 0) return 0;
	if (y < 0) return 0;
	
	screen = size();
	
	if (x > screen.x) return 0;
	if (y > screen.y) return 0;
	
	return 1;
}

void move(int x, int y) {
	POINT pos;
	GetCursorPos(&pos);
	SetCursorPos(pos.x + x, pos.y + y);
}

void moveTo(int x, int y) {
	SetCursorPos(x, y);
}

void scroll(int s) {
	INPUT ip = {0};
	
	ip.type = INPUT_MOUSE;
	ip.mi.mouseData = WHEEL_DELTA * s;
	ip.mi.dwFlags = MOUSEEVENTF_WHEEL;
	
	SendInput(1, &ip, sizeof(INPUT));
}

void click() {
	INPUT ip = {0};
	
	ip.type = INPUT_MOUSE;
	ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
	
	SendInput(1, &ip, sizeof(INPUT));
}

void rightClick() {
	INPUT ip = {0};
	
	ip.type = INPUT_MOUSE;
	ip.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP;
	
	SendInput(1, &ip, sizeof(INPUT));
}

void middleClick() {
	INPUT ip = {0};
	
	ip.type = INPUT_MOUSE;
	ip.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN | MOUSEEVENTF_MIDDLEUP;
	
	SendInput(1, &ip, sizeof(INPUT));
}

void mouseDown(enum MouseButtons button) {
	INPUT ip = {0};
	
	ip.type = INPUT_MOUSE;
	
	switch(button) {
		case MBS_LEFT:
			ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; break;
		case MBS_RIGHT:
			ip.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN; break;
		case MBS_MIDDLE:
			ip.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN; break;
		default:
			return;
	}
	
	SendInput(1, &ip, sizeof(INPUT));
}

void mouseUp(enum MouseButtons button) {
	INPUT ip = {0};
	
	ip.type = INPUT_MOUSE;
	
	switch(button) {
		case MBS_LEFT:
			ip.mi.dwFlags = MOUSEEVENTF_LEFTUP; break;
		case MBS_RIGHT:
			ip.mi.dwFlags = MOUSEEVENTF_RIGHTUP; break;
		case MBS_MIDDLE:
			ip.mi.dwFlags = MOUSEEVENTF_MIDDLEUP; break;
		default:
			return;
	}
	
	SendInput(1, &ip, sizeof(INPUT));
}

void drag(int x, int y, enum MouseButtons button) {
	mouseDown(button);
	move(x, y);
	Sleep(100);
	mouseUp(button);
}

void dragTo(int x, int y, enum MouseButtons button) {
	mouseDown(button);
	moveTo(x, y);
	Sleep(100);
	mouseUp(button);
}

void write(wchar_t *str) {
	size_t i, length;
	INPUT ip = {0};
	
	length = wcslen(str);
	
	for (i=0; i<length; i++) {
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = str[i];
		ip.ki.dwFlags = KEYEVENTF_UNICODE;
		
		SendInput(1, &ip, sizeof(INPUT));
	}
}

void writeEach(wchar_t *str, int time) {
	size_t i, length;
	INPUT ip = {0};
	
	length = wcslen(str);
	
	for (i=0; i<length; i++) {
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = str[i];
		ip.ki.dwFlags = KEYEVENTF_UNICODE;
		
		SendInput(1, &ip, sizeof(INPUT));
		
		Sleep(time);
	}
}

void keyDown(enum Keys key) {
	INPUT ip = {0};
	
	ip.type = INPUT_KEYBOARD;
	ip.ki.wVk = key;
	
	SendInput(1, &ip, sizeof(INPUT));
}

void keyUp(enum Keys key) {
	INPUT ip = {0};
	
	ip.type = INPUT_KEYBOARD;
	ip.ki.wVk = key;
	ip.ki.dwFlags |= KEYEVENTF_KEYUP;
	
	SendInput(1, &ip, sizeof(INPUT));
}

void press(enum Keys key) {
	keyDown(key);
	keyUp(key);
}

void hotkey(size_t count, ...) {
	size_t i;
	va_list args;
	va_start(args, count);
	
	for (i=0; i<count; i++)
		keyDown(va_arg(args, int));
	
	va_end(args);
	va_start(args, count);
	
	for (i=0; i<count; i++)
		keyUp(va_arg(args, int));
}
#define hotkey(...) hotkey(counter(L###__VA_ARGS__), __VA_ARGS__)

#endif /* C_AUTOGUI_IMPLEMENTATION */