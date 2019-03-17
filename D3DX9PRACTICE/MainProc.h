#pragma once
class MainProc
{
public:
	MainProc();
	virtual ~MainProc();

private:
	Mesh *mesh;
	Mesh *sphere;
	D3DXVECTOR3 spherePosition;
	MeshLoader *m_MeshLoader;

public:
	void Init();
	void Update();
	void Render();
	void Release();
	void ResetDevice();
};

