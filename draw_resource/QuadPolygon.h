#pragma once

#include"Shape.h"

class QuadPolygon : public Shape
{
public:
	QuadPolygon() = default;
	~QuadPolygon() = default;

private:

	virtual bool createVertexBuffer() noexcept override;

	virtual bool createIndexBuffer() noexcept override;
};

