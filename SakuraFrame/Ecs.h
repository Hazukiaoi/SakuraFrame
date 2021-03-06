#pragma once
//����www.youtube.com/watch?v=XsvI8Sng6dk
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

#define DEF_COMPONENT(className) virtual const char* ComponentName() { return #className; };

enum class COMPONENT_FILTER_TYPE
{
	ALL,
	ANY,
	NONE
};

class Component;
class Entity;

using ComponentID = std::size_t ;

inline ComponentID GetComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template<typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponent = 32;

using ComponentBitset = std::bitset<maxComponent>;
using ComponentArray = std::array<Component*, maxComponent>	;

class Component
{
public:
	DEF_COMPONENT(BASE);
	Entity* entity;

	virtual void Init() {};
	virtual void Update() {};

	virtual ~Component() {  };
};

class Entity
{
private:
	bool isActive = true;

	std::vector<std::unique_ptr<Component>> components;

public:
	std::string name;
	int instanceID;
	ComponentBitset componentBitset;
	ComponentArray componentArray;
	void Update()
	{
		for (auto& c : components) c->Update();
	}
	bool IsActive() const { return isActive; }
	void Destroy() { isActive = false; }

	template<typename T> 
	bool HasComponent() const
	{
		return componentBitset[GetComponentTypeID<T>()];
	}

	template<typename T, typename... TArgs>
	T& AddComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[GetComponentTypeID<T>()] = c;
		componentBitset[GetComponentTypeID<T>()] = true;

		c->Init();
		return *c;
	}

	template<typename T> T* GetComponent() const 
	{
		auto ptr(componentArray[GetComponentTypeID<T>()]);
		return static_cast<T*>(ptr);
	}
};

class ECSManager
{
private:

	template<typename T>
	void BitsetCheck(ComponentBitset& bs)
	{
		bs[GetComponentTypeID<T>()] = true;
	}

public:
	std::vector<std::unique_ptr<Entity>> entities;
	void Update()
	{
		for (auto& e : entities) e->Update();
	}

	void Refresh()
	{
		entities.erase(
			std::remove_if(std::begin(entities), std::end(entities), 
			[](const std::unique_ptr<Entity> &mEnity)
		{
			return !mEnity->IsActive();
		}), 
			std::end(entities));
	}

	void Clear()
	{
		entities.clear();
	}

	template<typename... Args>
	std::vector<Entity*> Filter()
	{
		ComponentBitset _bs;		
		int _i[] = {(BitsetCheck<Args>(_bs), 0)...};

		std::vector<Entity*> res;
		for (auto& e : entities)
		{
			if (_bs == e->componentBitset) res.emplace_back(e.get());
		}
		return res;
	}

	Entity& AddEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{e};
		entities.emplace_back(std::move(uPtr));
		return *e;
	}

	//template<typename T>
	//using FindEnt = bool(*)(Entity*, T);

	//template<typename T>
	//Entity& FindEntity(FindEnt<T> ft, T t)
	//{
	//	for (auto& e : entities)
	//	{
	//		if (ft(e.get(), t)) return *e.get();
	//	}
	//}
};