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

public:
	void Init();
	void Update();
	void Render();
	void Release();

	void ClockInit();
	void ClockUpdate();
	void ClockRender();
};

