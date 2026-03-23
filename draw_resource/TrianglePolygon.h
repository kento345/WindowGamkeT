#pragma once

#include"Shape.h"

class TrianglePolygon final : public Shape
{
	TrianglePolygon() = default;
	~TrianglePolygon() = default;

private:
	virtual bool createVertexBuffer() noexcept override;

	virtual bool createIndexBuffer() noexcept override;
};

