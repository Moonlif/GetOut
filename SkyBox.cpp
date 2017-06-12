#include "stdafx.h"
#include "SkyBox.h"

SkyBox::SkyBox()
{
}
SkyBox::~SkyBox()
{
	Destroy();
}

void SkyBox::Initialize(D3DXVECTOR3 center)
{
	int skyDistance = 145;

	/*sky[0] = new Sky;
	sky[0]->Initialize("Texture/sky/vanilla_sky_frost_up.jpg", D3DXVECTOR3(skyDistance, 0, skyDistance), D3DXVECTOR3(center.x, center.y + skyDistance, center.z));
	sky[1] = new Sky;
	sky[1]->Initialize("Texture/sky/vanilla_sky_frost_dn.jpg", D3DXVECTOR3(skyDistance, 0, skyDistance), D3DXVECTOR3(center.x, center.y - skyDistance, center.z));
	sky[2] = new Sky;
	sky[2]->Initialize("Texture/sky/vanilla_sky_frost_ft.jpg", D3DXVECTOR3(skyDistance, skyDistance, 0), D3DXVECTOR3(center.x, center.y, center.z + skyDistance));
	sky[3] = new Sky;
	sky[3]->Initialize("Texture/sky/vanilla_sky_frost_bk.jpg", D3DXVECTOR3(skyDistance, skyDistance, 0), D3DXVECTOR3(center.x, center.y, center.z - skyDistance));
	sky[4] = new Sky;
	sky[4]->Initialize("Texture/sky/vanilla_sky_frost_lf.jpg", D3DXVECTOR3(0, skyDistance, skyDistance), D3DXVECTOR3(center.x - skyDistance, center.y, center.z));
	sky[5] = new Sky;
	sky[5]->Initialize("Texture/sky/vanilla_sky_frost_rt.jpg", D3DXVECTOR3(0, skyDistance, skyDistance), D3DXVECTOR3(center.x + skyDistance, center.y, center.z));
*/
	sky[0] = new Sky;
	sky[0]->Initialize("Texture/sky/top.png", D3DXVECTOR3(skyDistance, 0, skyDistance), D3DXVECTOR3(center.x, center.y + skyDistance, center.z));
	sky[1] = new Sky;
	sky[1]->Initialize("Texture/sky/bottom.png", D3DXVECTOR3(skyDistance, 0, skyDistance), D3DXVECTOR3(center.x, center.y - skyDistance, center.z));
	sky[2] = new Sky;
	sky[2]->Initialize("Texture/sky/front.png", D3DXVECTOR3(skyDistance, skyDistance, 0), D3DXVECTOR3(center.x, center.y, center.z + skyDistance));
	sky[3] = new Sky;
	sky[3]->Initialize("Texture/sky/back.png", D3DXVECTOR3(skyDistance, skyDistance, 0), D3DXVECTOR3(center.x, center.y, center.z - skyDistance));
	sky[4] = new Sky;
	sky[4]->Initialize("Texture/sky/left.png", D3DXVECTOR3(0, skyDistance, skyDistance), D3DXVECTOR3(center.x - skyDistance, center.y, center.z));
	sky[5] = new Sky;
	sky[5]->Initialize("Texture/sky/right.png", D3DXVECTOR3(0, skyDistance, skyDistance), D3DXVECTOR3(center.x + skyDistance, center.y, center.z));
}

void SkyBox::Destroy()
{
	for (int i = 0; i < SKY_COUNT; i++)
	{
		SAFE_DELETE(sky[i]);
	}
}

void SkyBox::Render()
{
	for (int i = 0; i < SKY_COUNT; i++)
	{
		sky[i]->Render();
	}
}

