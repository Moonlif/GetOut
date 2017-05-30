#pragma once
#define g_pLightManager cLightManager::GetInstance()

class cLightManager
{
//public:
//	cLightManager();
//	~cLightManager();
private:
	SINGLETONE(cLightManager);

public:
	void SetSpotLight(DWORD nIndex, D3DXCOLOR Ambient, D3DXCOLOR Diffuse, D3DXCOLOR Specular, D3DXVECTOR3 pos,
		float range, float phi, float theta, D3DXVECTOR3 dir);
	void SetDirectionLight(DWORD nIndex, D3DXCOLOR Ambient, D3DXCOLOR Diffuse, D3DXCOLOR Specular, D3DXVECTOR3 dir);
	void SetPointLight(DWORD nIndex, D3DXCOLOR Ambient, D3DXCOLOR Diffuse, D3DXCOLOR Specular,
		D3DXVECTOR3 pos, float range);

};

