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
	map<wstring, vector <Material*>*> mMaterial;
	map<string, MeshLoader*> m_ObjMeshLoader;
	map<string, vector<MeshLoader*>> vObjAnime;

public:
	Mesh *AddMesh(string str, string route);
	vector<Material*>* AddMaterial(wstring name, vector<Material*>* mat);
	vector<MeshLoader*> AddObjAnime(string name, wstring route, int low, int high);
	MeshLoader *AddObjMesh(string str, wstring route);
	void RenderMesh(string str);

	void RenderMesh(MeshLoader *meshLoader, 
		D3DXVECTOR3 pos, 
		D3DXVECTOR3 rotation = { 0, 0, 0 }, 
		D3DXVECTOR3 scale	 = { 1, 1, 1 });
	void RenderAlphaMesh(MeshLoader *meshLoader,
		D3DXVECTOR3 pos,
		D3DXVECTOR3 rotation = { 0, 0, 0 },
		D3DXVECTOR3 scale = { 1, 1, 1 });
	void RenderPlanEffect(MeshLoader *meshLoader,
		Texture *tex,
		D3DXVECTOR3 pos,
		D3DXVECTOR3 rotation = { 0, 0, 0 },
		D3DXVECTOR3 scale = { 1, 1, 1 },
		D3DXCOLOR color = { 1, 1, 1, 1 });

	void Release();
};

#define MESHMANAGER MeshManager::GetInstance()