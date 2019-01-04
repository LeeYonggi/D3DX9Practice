#pragma once

struct VERTEX
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 texcoord;
};

struct CacheEntry
{
	UINT index;
	CacheEntry* pNext;
};

struct Material
{
	WCHAR   strName[MAX_PATH];

	D3DXVECTOR3 vAmbient;
	D3DXVECTOR3 vDiffuse;
	D3DXVECTOR3 vSpecular;

	int nShininess;
	float fAlpha;

	bool bSpecular;

	wstring   strTexture;
	IDirect3DTexture9* pTexture;
	D3DXHANDLE hTechnique;
};

class MeshLoader
{
public:
	MeshLoader();
	virtual ~MeshLoader();

public:
	HRESULT Create(IDirect3DDevice9* pd3dDevice, const WCHAR* strFilename);
	void    Destroy();


	UINT    GetNumMaterials() const
	{
		return m_Materials.GetSize();
	}
	Material* GetMaterial(UINT iMaterial)
	{
		return m_Materials.GetAt(iMaterial);
	}

	ID3DXMesh* GetMesh()
	{
		return m_pMesh;
	}
	WCHAR* GetMediaDirectory()
	{
		return m_strMediaDir;
	}

private:
	HRESULT LoadGeometryFromOBJ(wstring strFilename);
	HRESULT LoadMaterialsFromMTL(wstring strFileName);
	void    InitMaterial(Material* pMaterial);

	DWORD   AddVertex(UINT hash, VERTEX* pVertex);
	void    DeleteCache();

	IDirect3DDevice9* m_pd3dDevice;    // Direct3D Device object associated with this mesh
	ID3DXMesh* m_pMesh;         // Encapsulated D3DX Mesh

	CGrowableArray <CacheEntry*> m_VertexCache;   // Hashtable cache for locating duplicate vertices
	CGrowableArray <VERTEX> m_Vertices;      // Filled and copied to the vertex buffer
	CGrowableArray <DWORD> m_Indices;       // Filled and copied to the index buffer
	CGrowableArray <DWORD> m_Attributes;    // Filled and copied to the attribute buffer
	CGrowableArray <Material*> m_Materials;     // Holds material properties per subset

	WCHAR   m_strMediaDir[MAX_PATH];               // Directory where the mesh was found
};

