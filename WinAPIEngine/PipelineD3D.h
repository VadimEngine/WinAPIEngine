#pragma once
#include "GraphicsD3D.h"

class PipelineD3D {
public:
    bool isTexture;

    std::unique_ptr<class VertexShader> pvs;
    std::unique_ptr<class PixelShader> pps;

    //Microsoft::WRL::ComPtr<ID3DBlob> pvsBC;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;

    PipelineD3D(GraphicsD3D& gfx, Microsoft::WRL::ComPtr<ID3D11Device> pDevice, bool isTexture);

    Microsoft::WRL::ComPtr<ID3DBlob> pvsBC;

    Surface theSurface;

    void bind(GraphicsD3D& gfx, Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext);
};

