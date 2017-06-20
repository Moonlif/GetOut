#pragma once
#include "AllocateHierarchy.h"

class SkinnedMesh
{
	friend class SkinnedMeshManager;	//메니저에서는 SkinnedMesh를 마음껏 사용할 수 있게 하기 위해

public:
	SkinnedMesh(char* path, char* fileName);
	~SkinnedMesh();

	void Destroy();
	void UpdateAndRender();
	void SetAnimationIndex(int indexz);
	void SetAnimationIndexBlend(int nIndex);

	void SetRandomTrackPosition(); // 테스트용
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
	//하나만 생성
	Bone* rootFrame = nullptr;
	DWORD workingPaletteSize = 0;
	D3DXMATRIX* workingPalette = nullptr;
	LPD3DXEFFECT effect = nullptr;
	BoundingShere boundingSphere = BoundingShere();

	// 객체마다 생성
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

