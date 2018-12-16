#pragma once

struct Mesh
{
	LPD3DXMESH			mesh;
	D3DMATERIAL9		*material;
	LPDIRECT3DTEXTURE9	*tex;
	DWORD				numMaterial;
};

class MeshManager
	: public Singleton<MeshManager>
{
public:
	MeshManager();
	virtual ~MeshManager();

private:
	map<string, Mesh*> m_Mesh;

public:
	void AddMesh(string str);
	void RenderMesh(string str);
};

#define MESHMANAGER MeshManager::GetInstance()