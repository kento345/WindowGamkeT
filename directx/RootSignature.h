#pragma once

#include"Device.h"

class RootSignature
{
public:
	RootSignature() = default;

	~RootSignature() = default;

	bool create()noexcept;

	ID3D12RootSignature* get()const noexcept;

private:
	Microsoft::WRL::ComPtr<ID3D12RootSignature>rootSignature_{};
};

