#pragma once
#include "d3d11.h"
#pragma comment(lib, "d3d11.lib")

class SwapChain;
class DeviceContext;

class GEngine {
public:

	GEngine();
	~GEngine();

	static GEngine* Get();

	bool init(HWND _hWnd);
	bool initCore();
	bool initSwapChain(HWND hWnd, int width, int height);
	bool clearRT(float R, float G, float B, float A);
	bool present(bool vsync);

	bool release();
private:
	HWND hWnd;

	ID3D11Device *			m_pD3DDevice;
	D3D_FEATURE_LEVEL		m_featureLevel;
	IDXGIDevice*			m_pDXGIDevice;
	IDXGIAdapter*			m_pDXGIAdapter;
	IDXGIFactory*			m_pDXGIFactory;
	ID3D11DeviceContext*	m_pImmediateDeviceContext;
	IDXGISwapChain*			m_pSwapChain;
	ID3D11RenderTargetView* m_pRenderTargetView;
};

