#pragma once

struct Mesh
{
	LPD3DXMESH			mesh;
	LPD3DXPMESH			pmesh;
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
	void AddMesh(string str, string route);
	void RenderMesh(string str);
};

#define MESHMANAGER MeshManager::GetInstance()