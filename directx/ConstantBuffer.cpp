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
    
}