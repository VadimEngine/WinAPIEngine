#pragma once
#include "Bindable.h"

class Topology : public Bindable {
public:
	Topology(GraphicsD3D& gfx, D3D11_PRIMITIVE_TOPOLOGY type);
	void Bind(GraphicsD3D& gfx) noexcept override;
protected:
	D3D11_PRIMITIVE_TOPOLOGY type;
};