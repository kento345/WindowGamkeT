#pragma once

#include<Windows.h>
#include<cstdint>
#include<array>


class Input final
{
public:
	static Input& instance()noexcept {
		static Input instance;
		return instance;
	}

	bool getKey(uint16_t sKey)const noexcept;

	bool getTrigger(uint16_t sKey)const noexcept;

	void updateKeyState(void* pState)noexcept;

	void updatePrevKeyState()noexcept;

private:
	Input() = default;
	~Input() = default;

	Input(const Input& r) = delete;
	Input& operator=(const Input& r) = delete;
	Input(Input&& r) = delete;
	Input& operator =(Input&& r) = delete;

private:
	std::array<byte, 256>keyState_{};
	std::array<byte, 256>prevKeyState_{};
};

