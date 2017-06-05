#include "stdafx.h"
#include "SkinnedMeshManager.h"


SkinnedMeshManager::SkinnedMeshManager()
{
}


SkinnedMeshManager::~SkinnedMeshManager()
{
}

void SkinnedMeshManager::Destroy()
{
	for (auto iter = skinnedMeshData.begin(); iter != skinnedMeshData.end(); ++iter)
	{
		//SAFE_DELETE(iter->second);
		if (iter->second)
		{
			iter->second->Destroy();
			iter->second = nullptr;
		}
	}
	skinnedMeshData.clear();
}

SkinnedMesh* SkinnedMeshManager::GetSkinnedMesh(char* path, char* fileName)
{
	char directory[256];
	strcpy_s(directory, XFILE_DIRECTORY);
	strcat_s(directory, path);

	if (skinnedMeshData.find(fileName) == skinnedMeshData.end())
	{
		SkinnedMesh* skinnedMesh = new SkinnedMesh();
		skinnedMesh->Load(directory, fileName);
		skinnedMeshData[fileName] = skinnedMesh;
	}
	return skinnedMeshData[fileName];
}