#include <windows.h>
#include <stdarg.h>
#include "c-autogui.h"

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

void mouseDown(MouseButtons button) {
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

void mouseUp(MouseButtons button) {
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

void drag(int x, int y, MouseButtons button) {
	mouseDown(button);
	move(x, y);
	Sleep(100);
	mouseUp(button);
}

void dragTo(int x, int y, MouseButtons button) {
	mouseDown(button);
	moveTo(x, y);
	Sleep(100);
	mouseUp(button);
}

void write(wchar_t *str) {
	int i;
	INPUT ip = {0};
	size_t length;
	
	length = wcslen(str);
	
	for (i=0; i<length; i++) {
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = str[i];
		ip.ki.dwFlags = KEYEVENTF_UNICODE;
		
		SendInput(1, &ip, sizeof(INPUT));
	}
}

void writeEach(wchar_t *str, int time) {
	int i;
	INPUT ip = {0};
	size_t length;
	
	length = wcslen(str);
	
	for (i=0; i<length; i++) {
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = str[i];
		ip.ki.dwFlags = KEYEVENTF_UNICODE;
		
		SendInput(1, &ip, sizeof(INPUT));
		
		Sleep(time);
	}
}

void keyDown(Keys key) {
	INPUT ip = {0};
	
	ip.type = INPUT_KEYBOARD;
	ip.ki.wVk = key;
	
	SendInput(1, &ip, sizeof(INPUT));
}

void keyUp(Keys key) {
	INPUT ip = {0};
	
	ip.type = INPUT_KEYBOARD;
	ip.ki.wVk = key;
	ip.ki.dwFlags |= KEYEVENTF_KEYUP;
	
	SendInput(1, &ip, sizeof(INPUT));
}

void press(Keys key) {
	keyDown(key);
	keyUp(key);
}

void _hotkey(size_t count, ...) {
	int i;
	va_list args;
	va_start(args, count);
	
	for (i=0; i<count; i++)
		keyDown(va_arg(args, int));
	
	va_end(args);
	va_start(args, count);
	
	for (i=0; i<count; i++)
		keyUp(va_arg(args, int));
}
