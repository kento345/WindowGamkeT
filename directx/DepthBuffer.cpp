#include "DepthBuffer.h"
#include"DescriptorHeap.h"
#include"../window/Window.h"
#include<cassert>

namespace {
	constexpr auto heapType_ = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
}

DepthBuffer::~DepthBuffer()noexcept {
}

bool DepthBuffer::create()noexcept {
	//const auto [w, h] = Window::instance().size();

	D3D12_HEAP_PROPERTIES heapProps{};
	heapProps.Type = D3D12_HEAP_TYPE_DEFAULT;
}