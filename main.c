#include <stdlib.h>
#include "c-autogui.h"

int main() {
	system("start notepad");
	Sleep(1000);
	
	write(L"Hello, world!");
	press(ENTER);
	
	writeEach(L"321", 1000);
	
	write(L" bye \u263b");
	
	Sleep(900);
	
	hotkey(LCTRL, A);
	press(BACKSPACE);
	
	hotkey(LALT, F4);
	
	return 0;
}
