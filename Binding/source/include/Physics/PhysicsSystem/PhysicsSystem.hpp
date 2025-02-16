#pragma once
#include "Core/ECS/IECSSystem.h"
#include <ToolBoxMathHeaders.h>


struct CollisionPoint;
struct Collider;
class Rigidbody;
class Transfrom;

class PhysicsSystem : public IEcsSystem
{
public:
	ImplementIEcsSystem;


	static inline Vector3 gravity = Vector3(0,-9.81f,0);

	void AddForce(Rigidbody& rb, const Vector3& forces);


	PhysicsSystem(){};
	~PhysicsSystem(){};
private:

	void ApplieGravity(Scene* scene,std::vector<Rigidbody>* rigidBodys);
	void CollisionRespond(Scene* scene, std::vector<Rigidbody>* rigidBodys);
	void ApplieForces(Scene* scene, std::vector<Rigidbody>* rigidBodys);
	Collider* GetCollider(Scene* scene, uint32_t EntityID);
	void UpdateDrag(Rigidbody& rb);
};

