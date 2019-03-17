#pragma once

class Ground;
class Object
{
public:
	Object();
	virtual ~Object();

protected:
	Vector3 pos;
	Vector3 rotation;
	Vector3 scale;
	MeshLoader *meshLoader;

	bool destroy;
	bool active;
	float objRadius;

public:
	virtual void Init()		PURE;
	virtual void Update()	PURE;
	virtual void Render()	PURE;
	virtual void Release()	PURE;

public:
	bool IsCollisionGround(Vector3 vec3, Ground *map);
	bool IsCollisionCircle(Vector3 p1, Vector3 p2, float r1, float r2);
	float GetVec2Angle(Vector2 distance);
	Vector2 GetVec2TrackingPos(Vector3 p1);
	float GetDotRotationLerp(const float &p1, const float &p2);

public:
	Vector3 GetPos() { return pos; };
	void SetPos(Vector3 _pos) { pos = _pos; }
	
	Vector3 GetRotation() { return rotation; }
	void SetRotation(Vector3 _rotation) { rotation = _rotation; }

	Vector3 GetSize() { return scale; }
	void SetSize(Vector3 _size) { scale = _size; }

	MeshLoader *GetMeshLoader() { return meshLoader; }
	void SetMeshLoader(MeshLoader *_meshLoader) { meshLoader = _meshLoader; }

	bool GetDestroy() { return destroy; }
	void SetDestroy(bool _destroy) { destroy = _destroy; }

	bool GetActive() { return active; }
	void SetActive(bool _active) { active = _active; }

	float GetRadius() { return objRadius; }
	void SetRadius(float f) { objRadius = f; }
};

