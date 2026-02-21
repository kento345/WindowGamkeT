#pragma once

#include"Device.h"

class Fence final
{
public:
	Fence() = default;

	~Fence() = default;

	bool create()noexcept;

	void wait(UINT64 fenceValue)const noexcept;

	ID3D12Fence* get()const noexcept;

private:
	Microsoft::WRL::ComPtr<ID3D12Fence> fence_{};
	HANDLE waitGpuEvent_{};
};