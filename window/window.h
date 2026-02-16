#pragma once

#include<Windows.h>
#include<string>


class Window final
{
public:
	struct Window& instance()noexcept
	{
		static Window instance;
		return instance;
	}

	HRESULT create(HINSTANCE instance, int width, int heigth, std::string_view name)noexcept;

	bool messageLoop()const noexcept;

	HWND handle()const noexcept;

	std::pair<int, int>size()const noexcept;
private:
	Window() = default;
	~Window() = default;

	Window(const Window& r) = delete;
	Window& operator=(const Window& r) = delete;
	Window(Window&& r) = delete;
	Window& operator = (Window&& r) = delete;

private:
	HWND handle_{};
	int width_{};
	int height_{};
};

