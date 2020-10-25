#include "Graphics.h"
#include "Camera.h"
#include "RenderableMesh.h"
#include <sstream>
#include <d3dcompiler.h>
#include <cmath>
#include <DirectXMath.h>
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#include "CustomTimer.h"
#include "Surface.h"
#include "VertexShader.h"
#include "PixelShader.h"



#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")



Graphics::Graphics(HWND hWnd) 
: theSurface(Surface::FromFile("Images\\font.png")){
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	// create device and front/back buffers, and swap chain and rendering context
	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	);
	// gain access to texture subresource in swap chain (back buffer)
	Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
	pSwap->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget);

	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSState;
	pDevice->CreateDepthStencilState(&dsDesc, &pDSState);

	//bind depth state
	pContext->OMSetDepthStencilState(pDSState.Get(), 1u);
	// create depth stencil texture
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = 640;
	descDepth.Height = 480;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);

	// create view of depth stencil texture
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0u;
	pDevice->CreateDepthStencilView(pDepthStencil.Get(), &descDSV, &pDSV);

	// bind depth stencil view to OM
	pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), pDSV.Get());

	D3D11_VIEWPORT vp;
	vp.Width = 800.0f;
	vp.Height = 600.0f;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	pContext->RSSetViewports(1u, &vp);

	ImGui_ImplDX11_Init(pDevice.Get(), pContext.Get());

	//this->theSurface = Surface::FromFile("Images\\font.png");

	//initMixColorShaders();
	//initTextureShaders();


	//start create image pixel shader

	buildTexturePointers();

	//pMeshvs = std::make_unique<VertexShader>(*this, L"LearningVS.cso");
	//pMeshps = std::make_unique<PixelShader>(*this, L"LearningPS.cso");


	//end of create image pixel shader

	//setImageShaders();

	buildMeshPointers();
	//setMeshShaders();

	buildCharMap();

	
}

void Graphics::buildCharMap() {
	charKeyMap.insert({ 'A', {0,0} });
	charKeyMap.insert({ 'B', {1,0} });
	charKeyMap.insert({ 'C', {2,0} });
	charKeyMap.insert({ 'D', {3,0} });
	charKeyMap.insert({ 'E', {4,0} });
	charKeyMap.insert({ 'F', {5,0} });
	charKeyMap.insert({ 'G', {6,0} });
	charKeyMap.insert({ 'H', {7,0} });
	charKeyMap.insert({ 'I', {8,0} });
	charKeyMap.insert({ 'J', {9,0} });
	charKeyMap.insert({ 'K', {10,0} });
	charKeyMap.insert({ 'L', {11,0} });
	charKeyMap.insert({ 'M', {12,0} });
	charKeyMap.insert({ 'N', {13,0} });
	charKeyMap.insert({ 'O', {14,0} });
	charKeyMap.insert({ 'P', {15,0} });
	charKeyMap.insert({ 'Q', {16,0} });
	charKeyMap.insert({ 'R', {17,0} });
	charKeyMap.insert({ 'S', {18,0} });
	charKeyMap.insert({ 'T', {19,0} });
	charKeyMap.insert({ 'U', {20,0} });
	charKeyMap.insert({ 'V', {21,0} });
	charKeyMap.insert({ 'W', {22,0} });
	charKeyMap.insert({ 'X', {23,0} });
	charKeyMap.insert({ 'Y', {24,0} });
	charKeyMap.insert({ 'Z', {25,0} });

	charKeyMap.insert({ '.', {26,0} });
	charKeyMap.insert({ ',', {27,0} });

	charKeyMap.insert({ 'a', {0,1} });
	charKeyMap.insert({ 'b', {1,1} });
	charKeyMap.insert({ 'c', {2,1} });
	charKeyMap.insert({ 'd', {3,1} });
	charKeyMap.insert({ 'e', {4,1} });
	charKeyMap.insert({ 'f', {5,1} });
	charKeyMap.insert({ 'g', {6,1} });
	charKeyMap.insert({ 'h', {7,1} });
	charKeyMap.insert({ 'i', {8,1} });
	charKeyMap.insert({ 'j', {9,1} });
	charKeyMap.insert({ 'k', {10,1} });
	charKeyMap.insert({ 'l', {11,1} });
	charKeyMap.insert({ 'm', {12,1} });
	charKeyMap.insert({ 'n', {13,1} });
	charKeyMap.insert({ 'o', {14,1} });
	charKeyMap.insert({ 'p', {15,1} });
	charKeyMap.insert({ 'q', {16,1} });
	charKeyMap.insert({ 'r', {17,1} });
	charKeyMap.insert({ 's', {18,1} });
	charKeyMap.insert({ 't', {19,1} });
	charKeyMap.insert({ 'u', {20,1} });
	charKeyMap.insert({ 'v', {21,1} });
	charKeyMap.insert({ 'w', {22,1} });
	charKeyMap.insert({ 'x', {23,1} });
	charKeyMap.insert({ 'y', {24,1} });
	charKeyMap.insert({ 'z', {25,1} });

	charKeyMap.insert({ '0', {0,2} });
	charKeyMap.insert({ '1', {1,2} });
	charKeyMap.insert({ '2', {2,2} });
	charKeyMap.insert({ '3', {3,2} });
	charKeyMap.insert({ '4', {4,2} });
	charKeyMap.insert({ '5', {5,2} });
	charKeyMap.insert({ '6', {6,2} });
	charKeyMap.insert({ '7', {7,2} });
	charKeyMap.insert({ '8', {8,2} });
	charKeyMap.insert({ '9', {9,2} });
	charKeyMap.insert({ ':', {14,2} });
}


Graphics::~Graphics()
{
	ImGui_ImplDX11_Shutdown();
}

void Graphics::EndFrame() {
	// imgui frame end
	if (imguiEnabled)
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	pSwap->Present(1u, 0u);
}

void Graphics::BeginFrame(float red, float green, float blue) noexcept {
	// imgui begin frame
	if (imguiEnabled)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}
	
	const float color[] = { red,green,blue,1.0f };
	pContext->ClearRenderTargetView(pTarget.Get(), color);
	pContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::DrawIndexed(UINT count) noexcept
{
	pContext->DrawIndexed(count, 0u, 0u);
}

void Graphics::SetProjection(DirectX::FXMMATRIX proj) noexcept {
	projection = proj;
}

DirectX::XMMATRIX Graphics::GetProjection() const noexcept {
	return projection;
}


void Graphics::SetCamera(DirectX::FXMMATRIX cam) noexcept
{
	camera = cam;
}

DirectX::XMMATRIX Graphics::GetCamera() const noexcept
{
	return camera;
}

void Graphics::EnableImgui() noexcept
{
	imguiEnabled = true;
}

void Graphics::DisableImgui() noexcept
{
	imguiEnabled = false;
}

bool Graphics::IsImguiEnabled() const noexcept
{
	return imguiEnabled;
}


void Graphics::DrawTestTriange(float angle, float x, float z) {
	//Shaders are written HLSL (Hight level shader language)
	struct Vertex {
		struct{
			float x;
			float y;
			float z;
		} pos;
	};
	//Create vertex buffer (1 2d triangle at center of screen)
	Vertex vertices[] = {
		{ -1.0f, -1.0f, -1.0f},
		{ 1.0f, -1.0f, -1.0f},
		{ -1.0f, 1.0f, -1.0f},
		{ 1.0f, 1.0f, -1.0f },
		{ -1.0f, -1.0f, 1.0f},
		{ 1.0f, -1.0f, 1.0f },
		{ -1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f },
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices;
	pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer);

	//Bind vertex buffer to pipeline
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	//IA = Input assembler
	pContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);



	//create index buffer
	const unsigned short indices[] = {
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = sizeof(indices);
	ibd.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;
	pDevice->CreateBuffer(&ibd, &isd, &pIndexBuffer);

	pContext->IASetIndexBuffer( pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);


	// Create constant buffer for transformation matrix
	struct ConstanstBuffer {
		DirectX::XMMATRIX transform;
	};

	const ConstanstBuffer cb = {
		{
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixRotationZ(angle) *
				DirectX::XMMatrixRotationX(angle)*
				DirectX::XMMatrixTranslation(x, 0, z + 4.0) *
				DirectX::XMMatrixPerspectiveLH(1.0f, 1.0f, 0.5, 10.0f)
			)
		}
	};


	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;
	pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer);

	// bind constant buffer to vertex shader
	pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());


	struct ConstantBuffer2 {
		struct {
			float r;
			float g;
			float b;
			float a;
		} face_colors[6];
	};
	const ConstantBuffer2 cb2 = {
		{
			{1.0f,0.0f,1.0f},
			{1.0f,0.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,0.0f,1.0f},
			{1.0f,1.0f,0.0f},
			{0.0f,1.0f,1.0f}
		}
	};
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer2;
	D3D11_BUFFER_DESC cbd2;
	cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd2.Usage = D3D11_USAGE_DEFAULT;
	cbd2.CPUAccessFlags = 0u;
	cbd2.MiscFlags = 0u;
	cbd2.ByteWidth = sizeof(cb2);
	cbd2.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd2 = {};
	csd2.pSysMem = &cb2;
	pDevice->CreateBuffer(&cbd2, &csd2, &pConstantBuffer2);

	// bind constant buffer to pixel shader
	pContext->PSSetConstantBuffers(0u, 1u, pConstantBuffer2.GetAddressOf());

	//create pixel shader
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
	pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);

	//bind pixel shader
	pContext->PSSetShader(pPixelShader.Get(), 0, 0);

	//create vertex shader
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
	pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

	//bind vertex shader
	pContext->VSSetShader(pVertexShader.Get(), 0, 0);


	// input (vertex) layout (2nd position)
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		//"position" match in vertex shader
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Color",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
	};

	pDevice->CreateInputLayout(ied, (UINT)std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);

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

	pContext->DrawIndexed((UINT)std::size(indices), 0u, 0u);
}


void Graphics::startFrame() {
	BeginFrame(0.5f, 0.0f, 0.5f);
	theVertices.clear();
	theIndices.clear();
}

void Graphics::drawMesh(RenderableMesh& theMesh) {
	const unsigned int oldSize = theVertices.size() / 6;

	for (int i = 0; i < theMesh.vertices.size(); i++) {
		//add coordinate
		theVertices.push_back(theMesh.vertices[i].x);
		theVertices.push_back(theMesh.vertices[i].y);
		theVertices.push_back(theMesh.vertices[i].z);
		//add color...
		int theColor = theMesh.color;
		float red = (theColor >> 16) & 0x000000FF;
		float green = (theColor >> 8) & 0x000000FF;
		float blue = (theColor) & 0x000000FF;

		red /= 255.0f;
		green /= 255.0f;
		blue /= 255.0f;
		theVertices.push_back(red);
		theVertices.push_back(green);
		theVertices.push_back(blue);
	}

	for (int i = 0; i < theMesh.indicies.size(); i++) {
		unsigned int newIndex = theMesh.indicies[i] + oldSize;
		theIndices.push_back(newIndex);
	}
}

void Graphics::initMixColorShaders() {
	//shader stuff

	//create pixel shader
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	//D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
	D3DReadFileToBlob(L"LearningPS.cso", &pBlob);
	//D3DReadFileToBlob(L"TexturePS.cso", &pBlob);
	pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);

	//bind pixel shader
	pContext->PSSetShader(pPixelShader.Get(), 0, 0);

	//create vertex shader
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	//D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
	D3DReadFileToBlob(L"LearningVS.cso", &pBlob);
	//D3DReadFileToBlob(L"TextureVS.cso", &pBlob);
	pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

	//bind vertex shader
	pContext->VSSetShader(pVertexShader.Get(), 0, 0);

	// input (vertex) layout (2nd position)
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		//"position" match in vertex shader
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Color",0,     DXGI_FORMAT_R32G32B32A32_FLOAT,0,12 ,D3D11_INPUT_PER_VERTEX_DATA,0}
		//DXGI_FORMAT_R32G32_FLOAT
	};

	pDevice->CreateInputLayout(ied, (UINT)std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);

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
	//end of shader stuff


	//create texture
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
	static const auto s = Surface::FromFile("Images\\kappa50.png");


	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = s.GetWidth();
	textureDesc.Height = s.GetHeight();
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
	sd2.pSysMem = s.GetBufferPtr();
	sd2.SysMemPitch = s.GetWidth() * sizeof(Surface::Color);
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

	//Bind Texture to Pixel shader?
	pContext->PSSetShaderResources(0u, 1u, pTextureView.GetAddressOf());

	//samples
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;

	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	pDevice->CreateSamplerState(&samplerDesc, &pSampler);

	pContext->PSSetSamplers(0, 1, pSampler.GetAddressOf());
}

void Graphics::initTextureShaders() {
	//shader stuff

	//create pixel shader
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	//D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
	//D3DReadFileToBlob(L"LearningPS.cso", &pBlob);
	D3DReadFileToBlob(L"TexturePS.cso", &pBlob);
	pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);

	//bind pixel shader
	pContext->PSSetShader(pPixelShader.Get(), 0, 0);

	//create vertex shader
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	//D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
	//D3DReadFileToBlob(L"LearningVS.cso", &pBlob);
	D3DReadFileToBlob(L"TextureVS.cso", &pBlob);
	pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

	//bind vertex shader
	pContext->VSSetShader(pVertexShader.Get(), 0, 0);

	// input (vertex) layout (2nd position)
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		//"position" match in vertex shader
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TexCoord",0,     DXGI_FORMAT_R32G32_FLOAT,0,12 ,D3D11_INPUT_PER_VERTEX_DATA,0}
		//DXGI_FORMAT_R32G32_FLOAT
		//DXGI_FORMAT_R32G32B32A32_FLOAT
	};

	pDevice->CreateInputLayout(ied, (UINT)std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);

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
	//end of shader stuff


	//create texture
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
	static const auto s = Surface::FromFile("Images\\font.png");


	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = s.GetWidth();
	textureDesc.Height = s.GetHeight();
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
	sd2.pSysMem = s.GetBufferPtr();
	sd2.SysMemPitch = s.GetWidth() * sizeof(Surface::Color);
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

	//Bind Texture to Pixel shader?
	pContext->PSSetShaderResources(0u, 1u, pTextureView.GetAddressOf());

	//samples
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;

	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	/*
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	*/


	pDevice->CreateSamplerState(&samplerDesc, &pSampler);

	pContext->PSSetSamplers(0, 1, pSampler.GetAddressOf());
}


void Graphics::buildTexturePointers() {
	pvs = std::make_unique<VertexShader>(*this, L"TextureVS.cso");
	pps = std::make_unique<PixelShader>(*this, L"TexturePS.cso");

	pvsBC = pvs->GetBytecode();

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
}

void Graphics::buildMeshPointers() {
	pMeshvs = std::make_unique<VertexShader>(*this, L"LearningVS.cso");
	pMeshps = std::make_unique<PixelShader>(*this, L"LearningPS.cso");

	pMeshvsBC = pMeshvs->GetBytecode();

	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		//"position" match in vertex shader
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Color",0,     DXGI_FORMAT_R32G32B32A32_FLOAT,0,12 ,D3D11_INPUT_PER_VERTEX_DATA,0}
		//DXGI_FORMAT_R32G32_FLOAT
	};

	pDevice->CreateInputLayout(ied, (UINT)std::size(ied), pMeshvsBC->GetBufferPointer(), pMeshvsBC->GetBufferSize(), &pMeshInputLayout);
}



void Graphics::setImageShaders() {	
	//create vertex shader
	pps->Bind(*this);

	//bind vertex shader
	pvs->Bind(*this);

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
	//end of shader stuff

	//Bind Texture to Pixel shader?
	pContext->PSSetShaderResources(0u, 1u, pTextureView.GetAddressOf());

	pContext->PSSetSamplers(0, 1, pSampler.GetAddressOf());	
}

void Graphics::setMeshShaders() {
	pMeshvs->Bind(*this);
	pMeshps->Bind(*this);

	pContext->IASetInputLayout(pMeshInputLayout.Get());

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
	//end of shader stuff
}



void Graphics::drawFrame() {

	drawImage();
	setMeshShaders();


	//setMeshShaders();

	struct Vertex {
		struct {
			float x;
			float y;
			float z;
		} pos;
		struct{
			float r;
			float g;
			float b;
			float a;
		} col;
	};

	Vertex* vertices2 = new Vertex[theVertices.size()/6];
	for (int i = 0; i < theVertices.size(); i+=6) {
		float x = theVertices[i];
		float y = theVertices[i+1];
		float z = theVertices[i+2];

		float r = theVertices[i + 3];
		float g = theVertices[i + 4];
		float b = theVertices[i + 5];


		vertices2[i/6] = { x, y, -z,
							r, g, b, 1 };
	}

	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = theVertices.size() * sizeof(float);
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices2;//vertices.data();
	pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer);

	//Bind vertex buffer to pipeline
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	//IA = Input assembler
	pContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

	unsigned short* indices = new unsigned short[theIndices.size()];
	for (int i = 0; i < theIndices.size(); i++) {
		indices[theIndices.size() - 1 - i] = theIndices[i];
	}

	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = theIndices.size() * sizeof(unsigned short);
	ibd.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;//indices.data();
	pDevice->CreateBuffer(&ibd, &isd, &pIndexBuffer);

	pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);

	// Create constant buffer for transformation matrix
	struct ConstanstBuffer {
		DirectX::XMMATRIX transform;
	};

	float camAngle = CustomCamera->cameraFront.x;
	float camX = CustomCamera->cameraPos.x;
	float camY = CustomCamera->cameraPos.y;
	float camZ = CustomCamera->cameraPos.z;

	const ConstanstBuffer cb = {
		{
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixRotationZ(camAngle) *
				DirectX::XMMatrixRotationX(camAngle) *
				DirectX::XMMatrixTranslation(camX, 0, camZ + 4.0) *
				DirectX::XMMatrixPerspectiveLH(1.0f, 1.0f, 0.5, 10.0f)
			)
		}
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;
	pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer);

	// bind constant buffer to vertex shader
	pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());

							
	pContext->DrawIndexed((UINT)theIndices.size(), 0u, 0u);

	delete[] vertices2;
	delete[] indices;
	EndFrame();
}

void Graphics::drawImageTemp(float angle, float x, float z) {
	struct Vertex {
		struct {
			float x;
			float y;
			float z;
		} pos;
		struct {
			float x;
			float y;
		} color;
	};

	Vertex vertices[] = {
		{ 8.0f, -1.0f, 0,		1.0f, 1.0f},
		{ -1, 1.0f, 0,			0.0f, 0.0f},
		{ -1.0f, -1.0f, 0,		0.0f, 1.0f},
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices;
	pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer);

	//Bind vertex buffer to pipeline
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	//IA = Input assembler
	pContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

	//create index buffer
	const unsigned short indices[] = { 0,2,1 };

	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = sizeof(indices);
	ibd.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;
	pDevice->CreateBuffer(&ibd, &isd, &pIndexBuffer);

	pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);


	// Create constant buffer for transformation matrix
	struct ConstanstBuffer {
		DirectX::XMMATRIX transform;
	};

	const ConstanstBuffer cb = {
		{
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixRotationZ(angle) *
				DirectX::XMMatrixRotationX(angle) *
				DirectX::XMMatrixTranslation(x, 0, z + 4.0) *
				DirectX::XMMatrixPerspectiveLH(1.0f, 1.0f, 0.5, 10.0f)
			)
		}
	};


	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;
	pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer);

	// bind constant buffer to vertex shader
	pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());


	pContext->DrawIndexed((UINT)std::size(indices), 0u, 0u);
	EndFrame();
}

void Graphics::drawSubImage2(float x, float y, float z, float angle,
	float subX, float subY,
	float subWidth, float subHeight) {

	float size = 4;
	float width = (.06f / 2.0f) * size;
	float height = (.08f / 2.0f) * size;

	int texWidth = 256;
	int texHeight = 32;

	//x
	float theU = (subX + 1) * (subWidth / texWidth);
	//y
	float theV = (subY + 1) * (subHeight / texHeight);

	float theUstart = (subX) * (subWidth / texWidth);
	float theVstart = (subY) * (subHeight / texHeight);

	float drawX = x;
	float drawXRight = x + width;
	float drawY = y;
	float drawYDown = y - height;

	unsigned int oldSize = imageVertices.size() / 5;


	//float v1[] = { drawXRight, drawYDown, 0,	theU, theV };

	imageVertices.insert(imageVertices.end(), { drawXRight, drawYDown, 0, theU, theV });
	imageVertices.insert(imageVertices.end(), { drawX, drawYDown, 0,theUstart, theV });
	imageVertices.insert(imageVertices.end(), { drawX, drawY, 0, theUstart, theVstart });
	imageVertices.insert(imageVertices.end(), { drawXRight, drawY, 0, theU, theVstart });


	//const unsigned short indices[] = { 0,1,2, 3,0,2 };
	imageIndices.push_back(oldSize);
	imageIndices.push_back(oldSize + 1);
	imageIndices.push_back(oldSize + 2);
	imageIndices.push_back(oldSize + 3);
	imageIndices.push_back(oldSize);
	imageIndices.push_back(oldSize + 2);
}


void Graphics::drawImage() {
	setImageShaders();
	struct Vertex {
		struct {
			float x;
			float y;
			float z;
		} pos;
		struct {
			float x;
			float y;
		} color;
	};

	Vertex* vertices = new Vertex[imageVertices.size() / 5];

	for (int i = 0; i < imageVertices.size(); i+=5) {
		vertices[i/5] = {imageVertices[i],
					   imageVertices[i + 1],
					   imageVertices[i + 2],
					   imageVertices[i + 3],
					   imageVertices[i + 4] };
	}


	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = imageVertices.size() * sizeof(float);//sizeof(vertices);
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices;
	//TODO ACCESS VIOLATION HERE
	pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer);

	//Bind vertex buffer to pipeline
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	//IA = Input assembler
	pContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

	//create index buffer
	//const unsigned short indices[] = { 0,1,2, 3, 0,2 };
	unsigned short* indices = new unsigned short[imageIndices.size()];
	for (int i = 0; i < imageIndices.size(); i++) {
		indices[i] = imageIndices[i];
	}


	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = imageIndices.size() * sizeof(unsigned short);//sizeof(indices);
	ibd.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;
	pDevice->CreateBuffer(&ibd, &isd, &pIndexBuffer);

	pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);


	// Create constant buffer for transformation matrix
	struct ConstanstBuffer {
		DirectX::XMMATRIX transform;
	};

	/*
	float camAngle = CustomCamera->cameraFront.x;
	float camX = CustomCamera->cameraPos.x;
	float camY = CustomCamera->cameraPos.y;
	float camZ = CustomCamera->cameraPos.z;
	*/

	float camAngle = 0;
	float camX = 0;
	float camY = 0;
	float camZ = 0;

	const ConstanstBuffer cb = {
		{
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixRotationZ(camAngle) *
				DirectX::XMMatrixRotationX(camAngle) *
				DirectX::XMMatrixTranslation(camX, 0, camZ + 4.0) *
				DirectX::XMMatrixPerspectiveLH(1.0f, 1.0f, 0.5, 10.0f)
			)
		}
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;
	pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer);

	// bind constant buffer to vertex shader
	pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());


	pContext->DrawIndexed((UINT)imageIndices.size(), 0u, 0u);

	//std::stringstream ss;

	//ss << "Message: " << (imageVertices.size() / 5) << ": " << std::endl;
	//Print message name
	//OutputDebugString(ss.str().c_str());

	//EndFrame();

	delete[] vertices;
	delete[] indices;
	imageVertices.clear();
	imageIndices.clear();
}




void Graphics::drawSubImage(float x, float y, float z, float angle,
	float subX, float subY,
	float subWidth, float subHeight) {

	struct Vertex {
		struct {
			float x;
			float y;
			float z;
		} pos;
		struct {
			float x;
			float y;
		} color;
	};

	//image size is 256 X 32
	float size = 5;
	float width = (.06f / 2.0f) * size;
	float height = (.08f / 2.0f) * size;

	int texWidth = 256;
	int texHeight = 32;

	/*
	Vertex vertices[] = {
		{ x, y, 0,
		0 + (subX * (subWidth / texWidth)),
		1 - (subY * (subHeight / texHeight)) },

		{ x, y - height, 0,				
		0 + (subX * (subWidth / texWidth)),
		1 - ((subY + 1) * (subHeight / texHeight))},

		{ x + width, y - height,  0,	
		0 + ((subX + 1) * (subWidth / texWidth)),
		1 - ((subY + 1) * (subHeight / texHeight))},

		{ x + width, y,  0,
		0 + ((subX + 1) * (subWidth / texWidth)),
		1 - (subY * (subHeight / texHeight))},
	};
	*/
	/*
	Vertex vertices[] = {
		{ 8.0f, -1.0f, 0,	1.0f, 1.0f },
		{ -1, 1.0f, 0,			0.0f, 0.0f },
		{ -1.0f, -1.0f, 0,		0.0f, 1.0f },
	};
	
	/*
	Vertex vertices[] = {
	{ x, y, 0,							1.0f, 1.0f},
	{ x, y - height, 0,					0.0f, 0.0f},
	{ x + width, y - height,  0,		0.0f, 1.0f},
	{ x + width, y,  0,					1.0f, 0.0f}
	};
	*/
	/*
	Vertex vertices[] = {
		{ 8.0f, -1.0f, 0,		1.0f, 1.0f},
		{ -1.0f, -1.0f, 0,		0.0f, 1.0f },
		{ -1.0f, 1.0f, 0,		0.0f, 0.0f },
		{ 8.0f, 1.0f, 0,		1.0f, 0.0f }
	};
	*/
	//x
	float theU = (subX + 1) * (subWidth / texWidth);
	//y
	float theV = (subY + 1) * (subHeight / texHeight);

	float theUstart = (subX) * (subWidth / texWidth);
	float theVstart = (subY) * (subHeight / texHeight);

	float drawX = x;
	float drawXLeft = x + width;
	float drawY = y;
	float drawYDown = y - height;
	
	Vertex vertices[] = {
		{ drawXLeft, drawYDown, 0,	theU, theV},
		{ drawX, drawYDown, 0,		theUstart, theV },
		{ drawX, drawY, 0,			theUstart, theVstart },
		{ drawXLeft, drawY, 0,		theU, theVstart }
	};
	

	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices;
	pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer);

	//Bind vertex buffer to pipeline
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	//IA = Input assembler
	pContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

	//create index buffer
	const unsigned short indices[] = { 0,1,2, 3, 0,2 };

	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = sizeof(indices);
	ibd.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;
	pDevice->CreateBuffer(&ibd, &isd, &pIndexBuffer);

	pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);


	// Create constant buffer for transformation matrix
	struct ConstanstBuffer {
		DirectX::XMMATRIX transform;
	};

	const ConstanstBuffer cb = {
		{
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixRotationZ(angle) *
				DirectX::XMMatrixRotationX(angle) *
				DirectX::XMMatrixTranslation(x, 0, z + 4.0) *
				DirectX::XMMatrixPerspectiveLH(1.0f, 1.0f, 0.5, 10.0f)
			)
		}
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;
	pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer);

	// bind constant buffer to vertex shader
	pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());


	pContext->DrawIndexed((UINT)std::size(indices), 0u, 0u);
	EndFrame();
}




void Graphics::drawMesh(RenderableMesh& theMesh, float x, float y, float z, float angle) {

	struct Vertex {
		struct {
			float x;
			float y;
			float z;
		} pos;
	};
	//Create vertex buffer (1 2d triangle at center of screen)
	/*
	Vertex vertices[] = {
		{ -1.0f, -1.0f, -1.0f},
		{ 1.0f, -1.0f, -1.0f},
		{ -1.0f, 1.0f, -1.0f},
		{ 1.0f, 1.0f, -1.0f },
		{ -1.0f, -1.0f, 1.0f},
		{ 1.0f, -1.0f, 1.0f },
		{ -1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f },
	};
	*/
	//std::vector<Vertex> vertices;
	//TODO: should this be / 3?
	Vertex* vertices2 = new Vertex[theMesh.vertices.size()];
	for (int i = 0; i < theMesh.vertices.size(); i++) {
		glm::vec3 vert = theMesh.vertices[i];
		//vertices.push_back({ vert.x, vert.y, vert.z});
		vertices2[i] = { vert.x, vert.y, -vert.z };
	}

	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = theMesh.vertices.size() * 3 * sizeof(float);//vertices.size() * 3 * 4;//sizeof(vertices);
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem =vertices2;//vertices.data();
	pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer);

	//Bind vertex buffer to pipeline
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	//IA = Input assembler
	pContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

	//std::vector<unsigned int> indices;
	unsigned short* indices = new unsigned short[theMesh.indicies.size()];
	for (int i = 0; i < theMesh.indicies.size(); i++) {
		//indices.push_back(theMesh.indicies[i]);
		indices[theMesh.indicies.size() - 1 - i] = theMesh.indicies[i];
	}


	/*
	//create index buffer
	const unsigned short indices[] = {
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};
	*/

	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = theMesh.indicies.size() * sizeof(unsigned short);//indices.size() * 4;//sizeof(indices);
	ibd.StructureByteStride = sizeof(unsigned short);//sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;//indices.data();
	pDevice->CreateBuffer(&ibd, &isd, &pIndexBuffer);

	pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);


	// Create constant buffer for transformation matrix
	struct ConstanstBuffer {
		DirectX::XMMATRIX transform;
	};

	float camAngle = CustomCamera->cameraFront.x;
	float camX = CustomCamera->cameraPos.x;
	float camY = CustomCamera->cameraPos.y;
	float camZ = CustomCamera->cameraPos.z;

	const ConstanstBuffer cb = {
		{
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixRotationZ(camAngle) *
				DirectX::XMMatrixRotationX(camAngle) *
				DirectX::XMMatrixTranslation(camX, 0, camZ + 4.0) *
				DirectX::XMMatrixPerspectiveLH(1.0f, 1.0f, 0.5, 10.0f)
			)
		}
	};


	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;
	pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer);

	// bind constant buffer to vertex shader
	pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());


	struct ConstantBuffer2 {
		struct {
			float r;
			float g;
			float b;
			float a;
		} face_colors[6];
	};
	/*
	//need more colors...
	ConstantBuffer2* cb2 = new ConstantBuffer2[theMesh.indicies.size() / 3];
	for (int i = 0; i < theMesh.indicies.size() / 3; i++) {
		cb2[i] = {0.0f,0.0f,0.0f,1.0f};
	}
	*/

	int color = theMesh.color;
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	const ConstantBuffer2 cb2 = {
		{
			
			{r,0.0f,1.0f},
			{1.0f,0.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,0.0f,1.0f},
			{1.0f,1.0f,0.0f},
			{0.0f,1.0f,1.0f}
			/*
			{1.0f,1.0f,1.0f},
			{1.0f,1.0f,1.0f},
			{1.0f,1.0f,1.0f},
			{1.0f,1.0f,1.0f},
			{1.0f,1.0f,1.0f},
			{1.0f,1.0f,1.0f}
			*/
		}
	};
	
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer2;
	D3D11_BUFFER_DESC cbd2;
	cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd2.Usage = D3D11_USAGE_DEFAULT;
	cbd2.CPUAccessFlags = 0u;
	cbd2.MiscFlags = 0u;
	cbd2.ByteWidth = sizeof(cb2);//(theMesh.indicies.size() / 3) * 3 * 4;  //
	cbd2.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd2 = {};
	csd2.pSysMem = &cb2;
	pDevice->CreateBuffer(&cbd2, &csd2, &pConstantBuffer2);

	// bind constant buffer to pixel shader
	pContext->PSSetConstantBuffers(0u, 1u, pConstantBuffer2.GetAddressOf());
	
	//create pixel shader
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
	pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);

	//bind pixel shader
	pContext->PSSetShader(pPixelShader.Get(), 0, 0);

	//create vertex shader
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
	pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

	//bind vertex shader
	pContext->VSSetShader(pVertexShader.Get(), 0, 0);


	// input (vertex) layout (2nd position)
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		//"position" match in vertex shader
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	pDevice->CreateInputLayout(ied, (UINT)std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);

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

	//pContext->DrawIndexed((UINT)std::size(indices), 0u, 0u);
	pContext->DrawIndexed((UINT)theMesh.indicies.size(), 0u, 0u);

	delete[] vertices2;
	delete[] indices;
	//delete[] cb2;

}

void Graphics::setCamera(Camera* camera) {
	this->CustomCamera = camera;
}
void Graphics::drawString(std::string theString, float x, float y) {
	//convert x to normal float
	//conert y to normal float

	y *= 4;

	x = (x - (640.0f / 2.0f)) / (640.0f / 2.0f) - 3;
	y = -(y - (480.0f / 2.0f)) / (480 / 2.0f) + 3;
	
	for (int i = 0; i < theString.size(); i++) {
		if (charKeyMap.find(theString[i]) != charKeyMap.end()) {
			int charX = charKeyMap[theString[i]].x;
			int charY = charKeyMap[theString[i]].y;
			drawSubImage2((x) + i * .12f, (y), 0, 0,
				charX, charY, 6, 8);
		}

	}
}

std::string Graphics::toString() {
	return "Direct3D";
}