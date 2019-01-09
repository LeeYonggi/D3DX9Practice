#pragma once
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

public:
	virtual void Init()		PURE;
	virtual void Update()	PURE;
	virtual void Render()	PURE;
	virtual void Release()	PURE;

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
};

