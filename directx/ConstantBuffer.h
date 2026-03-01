#pragma once

#include"Device.h"
#include"DescriptorHeap.h"

class ConstantBuffer final
{
public:

	ConstantBuffer() = default;
	~ConstantBuffer() = default;
	bool create(UINT bufferSize)noexcept;
	ID3D12Resource* constantBuffer()const noexcept;
	D3D12_GPU_DESCRIPTOR_HANDLE getGpuDescriptorHandle()const noexcept;

private:
	Microsoft::WRL::ComPtr<ID3D12Resource> constantBuffer_{};
	UINT descriptorIndex_{};
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle_{};
};

