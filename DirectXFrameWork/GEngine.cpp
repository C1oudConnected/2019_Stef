#include "GEngine.h"



GEngine::GEngine()
{
}

GEngine::~GEngine()
{
}

bool GEngine::init(HWND _hWnd) {
	bool valid;
	hWnd = _hWnd;

	valid = initCore();
	if (!valid) return false;

	RECT rc;
	GetClientRect(hWnd, &rc);
	valid = initSwapChain(hWnd, rc.right - rc.left, rc.bottom - rc.top);
	if (!valid) return false;

	return true;
}

bool GEngine::initSwapChain(HWND hWnd, int width, int height)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	HRESULT res = GEngine::Get()->m_pDXGIFactory->CreateSwapChain(m_pD3DDevice, &swapChainDesc, &m_pSwapChain);
	if (FAILED(res))
		return false;

	ID3D11Texture2D* buffer = nullptr;
	res = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
	if (FAILED(res))
		return false;

	res = m_pD3DDevice->CreateRenderTargetView(buffer, NULL, &m_pRenderTargetView);

	buffer->Release();

	if (FAILED(res))
		return false;

	return true;
}

bool GEngine::clearRT(float R, float G, float B, float A)
{
	FLOAT final_color[] = { R,G,B,A };
	m_pImmediateDeviceContext->ClearRenderTargetView(m_pRenderTargetView, final_color);
	return true;
}

bool GEngine::present(bool vsync)
{
	return SUCCEEDED(m_pSwapChain->Present(vsync, NULL));
}

bool GEngine::initCore() {
	D3D_FEATURE_LEVEL feature_levels[] = {
		D3D_FEATURE_LEVEL_9_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_11_0
	};

	UINT feature_Levels_Num = ARRAYSIZE(feature_levels);

	HRESULT res;
	for (UINT it = feature_Levels_Num - 1; it >= 0; it--) {
		res = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
								NULL, &feature_levels[it], feature_Levels_Num, D3D11_SDK_VERSION,
								&m_pD3DDevice, &m_featureLevel, &m_pImmediateDeviceContext);
		if (SUCCEEDED(res))
			break;
	}

	if (!SUCCEEDED(res))
		return false;

	m_pD3DDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_pDXGIDevice);
	m_pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&m_pDXGIAdapter);
	m_pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_pDXGIFactory);

	return true;
}

bool GEngine::release()
{
	m_pDXGIDevice->				Release();
	m_pDXGIAdapter->			Release();
	m_pDXGIFactory->			Release();
	m_pImmediateDeviceContext->	Release();
	m_pD3DDevice->				Release();
	m_pSwapChain->				Release();
	m_pRenderTargetView->		Release();

	return true;
}

GEngine * GEngine::Get()
{
	static GEngine engine;
	return &engine;
}
