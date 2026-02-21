#include "CommandAllocator.h"
#include<cassert>

bool CommandAllocator::create(const D3D12_COMMAND_LIST_TYPE type)noexcept {
	type_ = type;
	const auto hr = Device::instance().get()->CreateCommandAllocator(type, IID_PPV_ARGS(&commandAllocator_));
	if (FAILED(hr)) {
		assert(false && "コマンドアロケータの作成に失敗しました");
		return false;
	}
	return true;
}

void CommandAllocator::reset() noexcept {

	if (!commandAllocator_) {
		assert(false && "コマンドアロケータが未作成です");
	}

	commandAllocator_->Reset();
}

ID3D12CommandAllocator* CommandAllocator::get()const noexcept {
	if (!commandAllocator_) {
		assert(false && "コマンドアロケータが未作成です");
	}
	return commandAllocator_.Get();
}

D3D12_COMMAND_LIST_TYPE CommandAllocator::getType() const noexcept {
	if(!commandAllocator_) {
		assert(false && "コマンドリストのタイプが未設定です");
	}
	return type_;
}