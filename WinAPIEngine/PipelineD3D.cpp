#include "PipelineD3D.h"
#include "VertexShader.h"
#include "PixelShader.h"


PipelineD3D::PipelineD3D(GraphicsD3D& gfx, Microsoft::WRL::ComPtr<ID3D11Device> pDevice, bool isTexture)
: theSurface(Surface::FromFile("Images\\font.png")), isTexture(isTexture) {
    if (isTexture) {
        pvs = std::make_unique<VertexShader>(gfx, L"TextureVS.cso");
        pps = std::make_unique<PixelShader>(gfx, L"TexturePS.cso");

        pvsBC = pvs->GetBytecode();

        // pass this in
        const D3D11_INPUT_ELEMENT_DESC ied[] = {
            //"position" match in vertex shader
            {"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT,0,12 ,D3D11_INPUT_PER_VERTEX_DATA,0}
        };

        pDevice->CreateInputLayout(ied, (UINT)std::size(ied), pvsBC->GetBufferPointer(), pvsBC->GetBufferSize(), &pInputLayout);

        D3D11_TEXTURE2D_DESC textureDesc = {};
        textureDesc.Width = theSurface.GetWidth();
        textureDesc.Height = theSurface.GetHeight();
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        textureDesc.CPUAccessFlags = 0;
        textureDesc.MiscFlags = 0;
        D3D11_SUBRESOURCE_DATA sd2 = {};
        sd2.pSysMem = theSurface.GetBufferPtr();
        sd2.SysMemPitch = theSurface.GetWidth() * sizeof(Surface::Color);
        Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture;
        pDevice->CreateTexture2D(
            &textureDesc, &sd2, &pTexture
        );

        // create the resource view on the texture
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = textureDesc.Format;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MostDetailedMip = 0;
        srvDesc.Texture2D.MipLevels = 1;

        pDevice->CreateShaderResourceView(
            pTexture.Get(), &srvDesc, &pTextureView
        );

        //samples
        D3D11_SAMPLER_DESC samplerDesc = {};
        samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
        samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

        pDevice->CreateSamplerState(&samplerDesc, &pSampler);
    } else {
        pvs = std::make_unique<VertexShader>(gfx, L"LearningVS.cso");
        pps = std::make_unique<PixelShader>(gfx, L"LearningPS.cso");

        pvsBC = pvs->GetBytecode();

        const D3D11_INPUT_ELEMENT_DESC ied[] = {
            //"position" match in vertex shader
            {"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"Color",0,     DXGI_FORMAT_R32G32B32A32_FLOAT,0,12 ,D3D11_INPUT_PER_VERTEX_DATA,0}
            //DXGI_FORMAT_R32G32_FLOAT
        };

        pDevice->CreateInputLayout(ied, (UINT)std::size(ied), pvsBC->GetBufferPointer(), pvsBC->GetBufferSize(), &pInputLayout);
    }
}

void PipelineD3D::bind(GraphicsD3D& gfx, Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext) {
    if (isTexture) {
        //bind vertex shader
        pps->Bind(gfx);
        //bind vertex shader
        pvs->Bind(gfx);
        // bind vertex layout
        pContext->IASetInputLayout(pInputLayout.Get());
        // Set primitive topology to triangle list (groups of 3 vertices)
        pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        //configure viewport
        D3D11_VIEWPORT vp;
        vp.Width = 640;
        vp.Height = 480;
        vp.MinDepth = 0;
        vp.MaxDepth = 1;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;
        pContext->RSSetViewports(1u, &vp);

        //Bind Texture to Pixel shader
        pContext->PSSetShaderResources(0u, 1u, pTextureView.GetAddressOf());

        pContext->PSSetSamplers(0, 1, pSampler.GetAddressOf());
    } else {
        //bind vertex shader
        pps->Bind(gfx);
        //bind vertex shader
        pvs->Bind(gfx);
        // bind vertex layout
        pContext->IASetInputLayout(pInputLayout.Get());
        // Set primitive topology to triangle list (groups of 3 vertices)
        pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        //configure viewport
        D3D11_VIEWPORT vp;
        vp.Width = 640;
        vp.Height = 480;
        vp.MinDepth = 0;
        vp.MaxDepth = 1;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;
        pContext->RSSetViewports(1u, &vp);
    }
}
