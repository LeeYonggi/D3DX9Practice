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

	D3DXVECTOR3 GetEye() { return m_Eye; }
	D3DXVECTOR3 GetAt() { return m_At; }
	D3DXVECTOR3 GetUp() { return m_Up; }
};

