#pragma once
#include "GraphicsD3D.h"

class Bindable {
public:
	virtual void Bind(GraphicsD3D& gfx) noexcept = 0;
	virtual ~Bindable() = default;
protected:
	static ID3D11DeviceContext* GetContext(GraphicsD3D& gfx) noexcept;
	static ID3D11Device* GetDevice(GraphicsD3D& gfx) noexcept;
};