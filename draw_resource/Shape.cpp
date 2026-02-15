#include "Shape.h"
#include<cassert>

bool Shape::create()noexcept
{
	if (!createVertexBuffer()) {
		return false;
	}
	if (!createIndexBuffer()) {
		return false;
	}
	return true;
}

void Shape::draw(const command_list& commandlist)noexcept
{
	commandlist.get()->IASetVertexBuffers(0, 1, &vertexBufferView_);
	commandlist.get()->IASetIndexBuffer(&indexBufferView_);
	commandlist.get()->IASetPrimitiveTopology(topology_);
	commandlist.get()->DrawIndexedInstanced(indexCount_, 1, 0, 0, 0);
}