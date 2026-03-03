#include "ConstantBuffer.h"
#include<cassert>


namespace {
	const auto heapType_ = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
}

ConstantBuffer::~ConstantBuffer() {
	DescriptorHeapContainer::instance().releaseDescriptor(heapType_, descriptorIndex_);
}

bool ConstantBuffer::create(UINT bufferSize)noexcept {
	const auto size = (sizeof(bufferSize) + 255) & ~255;

	D3D12_HEAP_PROPERTIES heapProps{};
	heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;
	D3D12_RESOURCE_DESC resorcesDesc{};
	resorcesDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resorcesDesc.Width = size;
	resorcesDesc.Height = 1;
	resorcesDesc.DepthOrArraySize = 1;
	resorcesDesc.MipLevels = 1;
	resorcesDesc.Format = DXGI_FORMAT_UNKNOWN;
	resorcesDesc.SampleDesc.Count = 1;
	resorcesDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	const auto res = Device::instance().get()->CreateCommittedResource(&heapProps,
		D3D12_HEAP_FLAG_NONE,
		&resorcesDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constantBuffer_));
	if (FAILED(res)) {
		assert(false && "コンスタントバッファーのディスクリプタ確保に失敗しました");
		return false;
	}

	const auto descriptorIndex = DescriptorHeapContainer::instance().allocateDescriptor(heapType_);
	if (!descriptorIndex.has_value()) {
		assert(false && "コンスタントバッファのディスクリプタ確保に失敗しました");
		return false;
	}

	descriptorIndex_ = descriptorIndex.value();

	auto heap = DescriptorHeapContainer::instance().get(heapType_);

	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc{};
	cbvDesc.BufferLocation = constantBuffer_->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = size;

	UINT cbvDescriptorSize = Device::instance().get()->GetDescriptorHandleIncrementSize(heapType_);

	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = heap->GetCPUDescriptorHandleForHeapStart();

	cpuHandle.ptr += descriptorIndex_ * cbvDescriptorSize;

	Device::instance().get()->CreateConstantBufferView(&cbvDesc, cpuHandle);

	gpuHandle_ = heap->GetGPUDescriptorHandleForHeapStart();

	gpuHandle_.ptr += descriptorIndex_ * cbvDescriptorSize;

	return true;
}

ID3D12Resource* ConstantBuffer::constantBuffer()const noexcept {
	assert(constantBuffer_ && "コンスタントバッファが未作成です");
	return constantBuffer_.Get();
}

D3D12_GPU_DESCRIPTOR_HANDLE ConstantBuffer::getGpuDescriptorHandle()const noexcept {
	assert(constantBuffer_ && "コンスタントバッファが未作成です");
	return gpuHandle_;
}