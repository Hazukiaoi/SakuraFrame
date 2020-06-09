#pragma once
//À´×Ôwww.youtube.com/watch?v=XsvI8Sng6dk
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

typedef std::size_t ComponentID;

inline ComponentID GetComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template<typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetComponentTypeID();
	return typeID();
}

constexpr std::size_t maxComponent = 32;

typedef std::bitset<maxComponent>				ComponentBitset;
typedef std::array<Component*, maxComponent>	ComponentArray;


class Component
{
public:
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

	ComponentBitset componentBitset;
	ComponentArray componentArray;
public:
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

		c->init();
		return *c;
	}

	template<typename T> T& GetComponent() const 
	{
		auto prt(componentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
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

	Entity& AddEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{e};
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};