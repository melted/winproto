/* main.cpp */

#include <Windows.h>

void DoPaint(HWND w) {
	PAINTSTRUCT ps;
	HDC dc;
	dc = BeginPaint(w, &ps);
	RECT textrect = { 100, 100, 300, 150 };
	DrawText(dc, L"This is the thing", -1, &textrect, 0);
	EndPaint(w, &ps);
}

LRESULT WndProc(HWND w, UINT msg, WPARAM wp, LPARAM lp) {
	LRESULT out = 0;
	switch(msg) {
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		DoPaint(w);
		break;
	default:
		return DefWindowProc(w, msg, wp, lp);
	}
	return out;
}

void MessagePump() {
	MSG msg;
	int res;
	while((res = GetMessage(&msg, NULL, 0, 0) != 0)) {
		if(res == -1) break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

bool InitWindow(HINSTANCE instance) {
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, 
		(WNDPROC)&WndProc, 0, 0, instance, NULL, NULL, NULL, NULL, L"Mini", NULL };
	if(!RegisterClassEx(&wc))
		return false;
	HWND win = CreateWindow(L"Mini", L"Nemo", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		640, 480, NULL, NULL, instance, NULL);
	if(!win)
		return false;
	ShowWindow(win, SW_SHOW);
	HCURSOR cursor = LoadCursor(NULL, IDC_ARROW);
	SetCursor(cursor);
	return true;
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev, LPSTR cmd, int show)
{
	if(InitWindow(instance))
		MessagePump();
	return 0;
}

