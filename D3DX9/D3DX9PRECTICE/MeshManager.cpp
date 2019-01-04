#include "DXUT.h"
#include "MeshManager.h"


MeshManager::MeshManager()
{
}


MeshManager::~MeshManager()
{
	Release();
}

Mesh *MeshManager::AddMesh(string str, string route)
{
	auto iter = m_Mesh.find(str);
	if (iter != m_Mesh.end()) return iter->second;

	ID3DXBuffer *mtrlBuff;
	ID3DXBuffer *adjBuff;
	Mesh *tempMesh = new Mesh;
	
	string temp = route + str;

	D3DXLoadMeshFromXA(temp.c_str(), D3DXMESH_MANAGED, DEVICE, &adjBuff,
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
			char ctr[128] = {};
			strcat(ctr, route.c_str());
			strcat(ctr, d3dMaterials[i].pTextureFilename);
			D3DXCreateTextureFromFileA(DEVICE, ctr, &tempMesh->tex[i]);
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

	return tempMesh;
}

MeshLoader * MeshManager::AddObjMesh(string str, wstring route)
{
	auto iter = m_ObjMeshLoader.find(str);
	if (iter != m_ObjMeshLoader.end()) iter->second;

	MeshLoader *temp = new MeshLoader;
	
	temp->Create(DEVICE, route.c_str());

	m_ObjMeshLoader.insert(make_pair(str, temp));

	return temp;
}

void MeshManager::CreateBoundingSphere(Mesh *meshinfo, D3DXVECTOR3 *center, float *radius)
{
	HRESULT hr;
	BYTE *v;

	meshinfo->mesh->LockVertexBuffer(0, (void**)&v);

	hr = D3DXComputeBoundingSphere(
		(D3DXVECTOR3*)v,
		meshinfo->mesh->GetNumVertices(),
		D3DXGetFVFVertexSize(meshinfo->mesh->GetFVF()),
		center,
		radius);

	meshinfo->mesh->UnlockVertexBuffer();
}
void MeshManager::RenderMesh(string str)
{
	auto iter = m_Mesh.find(str);
	if (iter == m_Mesh.end()) return;

	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	D3DXCOLOR col(1.0f, 1.0f, 1.0f, 1.0f);
	D3DLIGHT9 light = d3d::InitDirectionalLight(&dir, &col);

	DEVICE->SetLight(0, &light);
	DEVICE->LightEnable(0, true);
	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, true);

	//DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	//DEVICE->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	//DEVICE->SetRenderState(D3DRS_ZENABLE, true);

	D3DXMATRIX matS;
	D3DXMatrixScaling(&matS, 1, 1, 1);
	DEVICE->SetTransform(D3DTS_WORLD, &matS);

	for (int i = 0; i < iter->second->numMaterial; i++)
	{
		DEVICE->SetMaterial(&iter->second->material[i]);
		DEVICE->SetTexture(0, iter->second->tex[i]);

		iter->second->pmesh->DrawSubset(i);

		DEVICE->SetMaterial(&d3d::WHITE_MTRL);
		DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		iter->second->pmesh->DrawSubset(i);
		DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

void MeshManager::RenderMesh(MeshLoader * meshLoader, D3DXVECTOR3 pos, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
{
	D3DXMATRIX matW, matS, matRX, matRY, matRZ, matT;

	D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);
	D3DXMatrixRotationX(&matRX, rotation.x);
	D3DXMatrixRotationY(&matRY, rotation.y);
	D3DXMatrixRotationZ(&matRZ, rotation.z);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	matRX = matRX * matRY * matRZ;
	matW = matS * matRX * matT;

	DEVICE->SetTransform(D3DTS_WORLD, &matW);
	
	D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	D3DXCOLOR col(1.0f, 1.0f, 1.0f, 1.0f);
	D3DLIGHT9 light = d3d::InitDirectionalLight(&dir, &col);

	DEVICE->SetLight(0, &light);
	DEVICE->LightEnable(0, true);

	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, true);


	for (int i = 0; i < meshLoader->GetNumMaterials(); i++)
	{
		D3DMATERIAL9 mtl;

		mtl.Ambient = D3DXCOLOR(meshLoader->GetMaterial(i)->vAmbient.x, meshLoader->GetMaterial(i)->vAmbient.y, meshLoader->GetMaterial(i)->vAmbient.z, 1.f);
		mtl.Diffuse = D3DXCOLOR(meshLoader->GetMaterial(i)->vDiffuse.x, meshLoader->GetMaterial(i)->vDiffuse.y, meshLoader->GetMaterial(i)->vDiffuse.z, 1.f);
		mtl.Ambient = D3DXCOLOR(meshLoader->GetMaterial(i)->vSpecular.x, meshLoader->GetMaterial(i)->vSpecular.y, meshLoader->GetMaterial(i)->vSpecular.z, 1.f);
		mtl.Emissive = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		mtl.Power = 1.f;

		DEVICE->SetMaterial(&mtl);
		DEVICE->SetTexture(0, meshLoader->GetMaterial(i)->pTexture);
		meshLoader->GetMesh()->DrawSubset(i);
	}


}

void MeshManager::Release()
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

	for (auto iter : m_ObjMeshLoader)
	{
		iter.second->Destroy();
		SAFE_DELETE(iter.second);
	}
	m_ObjMeshLoader.clear();
}
