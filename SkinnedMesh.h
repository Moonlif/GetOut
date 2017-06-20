#pragma once
#include "AllocateHierarchy.h"

class SkinnedMesh
{
	friend class SkinnedMeshManager;	//�޴��������� SkinnedMesh�� ������ ����� �� �ְ� �ϱ� ����

public:
	SkinnedMesh(char* path, char* fileName);
	~SkinnedMesh();

	void Destroy();
	void UpdateAndRender();
	void SetAnimationIndex(int indexz);
	void SetAnimationIndexBlend(int nIndex);

	void SetRandomTrackPosition(); // �׽�Ʈ��
	inline void SetPosition(D3DXVECTOR3 v) { position = v; boundingSphere.center = v; }
	inline void SetSize(float s) { size = s; }
	inline void SetRotation(float rotation) { rotationAngle = rotation; }
	inline void SetDirection(D3DXVECTOR3 dir) { direction = dir; }
	inline void SetSpeed(float speed) { aniSpeed = speed; }
	inline void SetRender(bool is) { isRender = is; }

	inline const LPD3DXVECTOR3 GetPositionAdress() { return &position; }
	inline BoundingShere* GetBoundingSphere() { return &boundingSphere; }
	inline D3DXVECTOR3 GetDirection() { return direction; }
	inline float GetSize() { return size; }

private:
	//�ϳ��� ����
	Bone* rootFrame = nullptr;
	DWORD workingPaletteSize = 0;
	D3DXMATRIX* workingPalette = nullptr;
	LPD3DXEFFECT effect = nullptr;
	BoundingShere boundingSphere = BoundingShere();

	// ��ü���� ����
	LPD3DXANIMATIONCONTROLLER animController = nullptr;
	D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 direction = D3DXVECTOR3(0, 0, 1);
	float size = 1.0f;
	float rotationAngle = 0.0f;
	float aniSpeed = 0.0f;
	
	float m_fBlendTime;
	float m_fPassedBlendTime;
	bool m_isAnimBlend;
	
	bool isRender = true;

private:
	SkinnedMesh();

	void Load(char* path, char* fileName);
	LPD3DXEFFECT LoadEffect(char* fileName);
	void Update(Bone* current, D3DXMATRIXA16* parentMatrix);
	void Render(Bone* bone = nullptr);
	void SetupBoneMatrixPointers(Bone* bone);	
};

