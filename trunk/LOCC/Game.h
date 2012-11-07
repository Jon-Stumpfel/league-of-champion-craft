#pragma once

#include "IGameState.h"
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
class CGame
{

public:

	static CGame* GetInstance(void);

	void Initialize(HWND hWnd, HINSTANCE hInstance,
				int nScreenWidth, int nScreenHeight,
				bool bIsWindowed);

	bool Main(void);
	void Shutdown(void);
	void SetIsWindowed(bool win);
	int GetWindowWidth(void) { return m_nWidth;}
	int GetWindowHeight(void) { return m_nHeight;}
	HWND GetHWND(void) { return m_hWnd;}
	void SetDieThread(bool b) { m_bDieThreadIHateYou = b;}
	void SetShowFramerate(bool b) { m_bShowFramerate = b;}
private:

	CGame(void);
	~CGame(void);
	CGame(const CGame&);
	CGame& operator=(const CGame&);

	ID3DXEffect* texEffect;
	ID3DXMesh* teapotMesh;
	D3DXMATRIX teapotMatrix;
	D3DXVECTOR4 teapotColor;
	IDirect3DTexture9	*reflectTexture;
	D3DXMATRIX cam;
	D3DXMATRIX proj;
	// 3 actions for each frame:
		bool Input(void);
		void Update(void);
		void Render(void);
	int m_nWidth;		
	int m_nHeight;		
	HWND m_hWnd;
	bool m_bIsWindowed;
	DWORD m_dwCurrTime;
	IGameState* currentState;
	bool m_bUpdateFps;
	unsigned int m_nFrameCount;
	float m_fFrameElapsed;

	bool m_bShowFramerate;

	bool m_bDieThreadIHateYou;
};

