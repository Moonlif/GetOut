#pragma once
#include "SkinnedMesh.h"

class SkinnedMeshManager
{
private:
	SkinnedMeshManager();
	SkinnedMeshManager(const SkinnedMeshManager& other);
	~SkinnedMeshManager();

public:
	static SkinnedMeshManager& Get()
	{
		static SkinnedMeshManager instance;
		return instance;
	}

	void Destroy();

	SkinnedMesh* GetSkinnedMesh(char* path, char* fileName);

private:
	const char* XFILE_DIRECTORY = "./player/XFile/";

	std::map<std::string, SkinnedMesh*> skinnedMeshData;
};

