#include "DXUT.h"
#include "MeshManager.h"


MeshManager::MeshManager()
{
}


MeshManager::~MeshManager()
{
	for (auto iter : m_Mesh)
	{
		if (iter.second->material)
			delete[] iter.second->material;

		if (iter.second->tex)
		{
			for (int i = 0; i < iter.second->numMaterial; i++)
			{
				if (iter.second->tex[i])
					iter.second->tex[i]->Release();
			}
			delete[] iter.second->tex;
		}

		if (iter.second->mesh)
			iter.second->mesh->Release();
		if (iter.second->pmesh)
			iter.second->pmesh->Release();

		SAFE_DELETE(iter.second);
	}
	m_Mesh.clear();
}

void MeshManager::AddMesh(string str, string route)
{
	auto iter = m_Mesh.find(str);
	if (iter != m_Mesh.end()) return;

	ID3DXBuffer *mtrlBuff;
	ID3DXBuffer *adjBuff;
	Mesh *tempMesh = new Mesh;

	D3DXLoadMeshFromXA(route.c_str(), D3DXMESH_MANAGED, DEVICE, &adjBuff,
		&mtrlBuff, NULL, &tempMesh->numMaterial, &tempMesh->mesh);

	D3DXMATERIAL *d3dMaterials = (D3DXMATERIAL*)mtrlBuff->GetBufferPointer();
	tempMesh->material = new D3DMATERIAL9[tempMesh->numMaterial];
	tempMesh->tex	   = new LPDIRECT3DTEXTURE9[tempMesh->numMaterial];

	for (int i = 0; i < tempMesh->numMaterial; i++)
	{
		tempMesh->material[i] = d3dMaterials[i].MatD3D;
	
		tempMesh->material[i].Ambient = tempMesh->material[i].Diffuse;
		
		tempMesh->tex[i] = NULL;
		if (d3dMaterials[i].pTextureFilename != NULL &&
			strlen(d3dMaterials[i].pTextureFilename) > 0)
		{
			D3DXCreateTextureFromFileA(DEVICE, d3dMaterials[i].pTextureFilename, &tempMesh->tex[i]);
		}
	}
	m_Mesh.insert(make_pair(str, tempMesh));

	mtrlBuff->Release();


	tempMesh->mesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE, 
		(DWORD*)adjBuff->GetBufferPointer(),
		(DWORD*)adjBuff->GetBufferPointer(),
		0, 0);

	D3DXGeneratePMesh(
		tempMesh->mesh,
		(DWORD*)adjBuff->GetBufferPointer(),
		0,
		0,
		1,
		D3DXMESHSIMP_FACE,
		&tempMesh->pmesh);

	adjBuff->Release();

	int maxFaces = tempMesh->pmesh->GetMaxFaces();
	tempMesh->pmesh->SetNumFaces(maxFaces);
}

void MeshManager::RenderMesh(string str)
{
	auto iter = m_Mesh.find(str);
	if (iter == m_Mesh.end()) return;

	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	DEVICE->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	DEVICE->SetRenderState(D3DRS_ZENABLE, true);

	D3DXMATRIX matS;
	D3DXMatrixScaling(&matS, 1, 1, 1);
	DEVICE->SetTransform(D3DTS_WORLD, &matS);

	for (int i = 0; i < iter->second->numMaterial; i++)
	{
		DEVICE->SetMaterial(&iter->second->material[i]);
		DEVICE->SetTexture(0, iter->second->tex[i]);

		iter->second->pmesh->DrawSubset(i);
	}
}
