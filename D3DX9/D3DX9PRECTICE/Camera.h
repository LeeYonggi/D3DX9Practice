#pragma once

class Camera
{
public:
	Camera();
	virtual ~Camera();

protected:
	D3DXVECTOR3 m_Eye, m_At, m_Up;

public:
	void Init();
	void Translate(D3DXVECTOR3 eye, D3DXVECTOR3 at);
	void SetCamera(Vector3 eye, Vector3 at);
	virtual void CamUpdate() PURE;

};

