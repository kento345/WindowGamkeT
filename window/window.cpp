#include "Window.h"
#include"Input.h"

namespace {
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

HRESULT Window::create(HINSTANCE instance, int width, int height, std::string_view name)noexcept {
	WNDCLASS wc{};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = instance;
	wc.lpszClassName = name.data();
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	RegisterClass(&wc);

	handle_ = CreateWindow(wc.lpszClassName, wc.lpszClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, instance, nullptr);
    
	if (!handle_) {
		return E_FAIL;
	}

	ShowWindow(handle_, SW_SHOW);
	UpdateWindow(handle_);

	width_ = width;
	height_ = height;

	return S_OK;
}

bool Window::messageLoop()const noexcept {
	MSG msg{};

	Input::instance().updatePrevKeyState();
	while (PeekMessage(&msg,nullptr,0,0,PM_REMOVE))
	{
		if (msg.message == WM_QUIT) {
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);

		static byte keyState[256]{};
		if (GetKeyboardState(keyState)) {
			Input::instance().updateKeyState(keyState);
		}
	}
	return true;
}

HWND Window::handle()const noexcept {
	return handle_;
}

std::pair<int, int>Window::size()const noexcept {
	return { width_,height_ };
}
