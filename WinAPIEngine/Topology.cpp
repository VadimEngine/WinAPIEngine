#include "Topology.h"

Topology::Topology(GraphicsD3D& gfx, D3D11_PRIMITIVE_TOPOLOGY type)
	: type(type) {}

void Topology::Bind(GraphicsD3D& gfx) noexcept {
	GetContext(gfx)->IASetPrimitiveTopology(type);
}
