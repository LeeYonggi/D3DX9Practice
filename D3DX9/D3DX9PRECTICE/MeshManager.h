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
	map<string, MeshLoader*> m_ObjMeshLoader;

public:
	Mesh *AddMesh(string str, string route);
	MeshLoader *AddObjMesh(string str, wstring route);
	void CreateBoundingSphere(Mesh *meshinfo, D3DXVECTOR3 *center, float *radius);
	void RenderMesh(string str);

	void RenderMesh(MeshLoader *meshLoader, 
		D3DXVECTOR3 pos, 
		D3DXVECTOR3 rotation = { 0, 0, 0 }, 
		D3DXVECTOR3 scale	 = { 1, 1, 1 });

	void Release();
};

#define MESHMANAGER MeshManager::GetInstance()