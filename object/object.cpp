#include "object.h"


namespace game {

	void object::setDrawCommand(const command_list& commandlist, UINT slot)noexcept {
		commandlist.get()->SetGraphicsRootDescriptorTable(slot, constantBuffer.getGpuDescriptorHandle());
	}
}