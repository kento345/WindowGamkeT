#pragma once

#include"Device.h"
#include"SwapChain.h"
#include"DescriptorHeap.h"
#include<vector>

class RenderTarget final
{
public:
	RenderTarget() = default;
	~RenderTarget();

	bool createBackBuffer(const SwapChain& swapChain)noexcept;

	D3D12_CPU_DESCRIPTOR_HANDLE getCpuDescriptorHandle(UINT index)const noexcept;

	ID3D12Resource* get(UINT index)const noexcept;

private:
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> renderTargets_{};
};

