#include "CommandList.h"
#include<cassert>

bool CommandList::create(const CommandAllocator& allocator)noexcept {
	const auto hr = Device::instance().get()->CreateCommandList(0, allocator.getType(), allocator.get(), nullptr, IID_PPV_ARGS(&commandList_));
	if (FAILED(hr)) {
		assert(false && "コマンドリストの作成に失敗しました");
		return false;
	}

	commandList_->Close();
	return true;
}

void CommandList::reset(const CommandAllocator& allocator)noexcept {
	if (!commandList_) {
		assert(false && "コマンドリストが未作成です");
	}
	commandList_->Reset(allocator.get(), nullptr);
}

ID3D12GraphicsCommandList* CommandList::get()const noexcept {
	if (!commandList_) {
		assert(false && "コマンドリストが未作成です");
	}
	return commandList_.Get();
}