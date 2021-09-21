#include "utils.cpp"
#include <windows.h>
#include <WinUser.h>
#include <gdiplus.h>
global_variable bool running = true;

struct Render_State {
	int height, width;
	void* memory;
	BITMAPINFO bitmap_info;
};

global_variable Render_State render_state;

#include "platform_common.cpp"
#include "renderer.cpp"
#include "game.cpp"
#include "Images.h"
#include "settings.h"
#include <time.h>

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;
	//DisableMinimizeButton(hwnd);
	switch (uMsg) {
		case WM_CLOSE:

		case WM_DESTROY: {
			running = false;
		}break;

		case WM_SIZE: {
			RECT rect;
			GetClientRect(hwnd, &rect);
			render_state.width = rect.right - rect.left;
			render_state.height = rect.bottom - rect.top;

			int size = render_state.width * render_state.height * sizeof(unsigned int);

			//Check if buffer memory already has stuff in it
			//If so, free it up
			if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
			render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
			render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
			render_state.bitmap_info.bmiHeader.biHeight = render_state.height;	
			render_state.bitmap_info.bmiHeader.biPlanes = 1;
			render_state.bitmap_info.bmiHeader.biBitCount = 32;
			render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;
		}break;

		default:{
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	return result;
}



int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	//Create a Window Class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = L"Game Window Class";
	window_class.lpfnWndProc = window_callback;
	
	//Register the Class
	RegisterClass(&window_class);

	//Create Window
	HWND window = CreateWindow(window_class.lpszClassName, L"Assault on Atlantis", WS_MAXIMIZE | WS_VISIBLE | WS_OVERLAPPEDWINDOW ^ WS_MINIMIZEBOX^ WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);
	
	ShowCursor(false);

	Input input = {};

	float delta_time = 0.0166666f;
	
	//get cpu cycles
	LARGE_INTEGER frame_begin_time;
	QueryPerformanceCounter(&frame_begin_time);

	float performance_frequency; {
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		performance_frequency = (float)perf.QuadPart;
	}

	Init();

	//async thread showSeconds()

	srand(time(nullptr));
	StartCounter();
	int i = 0;

	while (running) {
		draw_image(-60, 410, titletext, 0);
		draw_image(570, 435, scoretext, 0);

		MSG message;

		for (int i = 0; i < BUTTON_COUNT; i++) {
			input.buttons[i].changed = false;
		}


		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {			
			switch (message.message) {
				case WM_KEYUP:

				case WM_KEYDOWN: {
					u32 vk_code = (u32)message.wParam;
					bool is_down = ((message.lParam & (1 << 31)) == 0);

					switch (vk_code) {
						case(VK_UP): {
							input.buttons[BUTTON_UP].is_down = is_down;
							input.buttons[BUTTON_UP].changed = true;
						} break;
						case(VK_LEFT): {
							input.buttons[BUTTON_LEFT].is_down = is_down;
							input.buttons[BUTTON_LEFT].changed = true;
						} break;
						case(VK_RIGHT): {
							input.buttons[BUTTON_RIGHT].is_down = is_down;
							input.buttons[BUTTON_RIGHT].changed = true;
						} break;
						case(VK_DOWN): {
							input.buttons[BUTTON_DOWN].is_down = is_down;
							input.buttons[BUTTON_DOWN].changed = true;
						} break;
						case(VK_SPACE): {
							input.buttons[BUTTON_SPACE].is_down = is_down;
							input.buttons[BUTTON_SPACE].changed = true;
						} break;
						case(VK_RETURN): {
							input.buttons[BUTTON_ENTER].is_down = is_down;
							input.buttons[BUTTON_ENTER].changed = true;
						} break;
					}
				} break;

				default: {
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
			}
		}

		//SIMULATE
		simulate_game(&input, delta_time);
		
		/*
		

		
		*/

		
		//cout << number << " is divisible by"

		//RENDER
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);

		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);
		delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performance_frequency;
		frame_begin_time = frame_end_time;
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);
}