#pragma once

#include <vector>
#include <unordered_map>
#include <functional>

// VECTOR, TRANSFORM AND RGB
struct Vector2D
{
	float x, y;

	static Vector2D ZeroVector;

	Vector2D();
	Vector2D(float pos_x, float pos_y);

	friend Vector2D operator+(const Vector2D& v1, const Vector2D& v2)
	{
		return Vector2D(v1.x + v2.x, v1.y + v2.y);
	}

	friend Vector2D operator-(const Vector2D& v1, const Vector2D& v2)
	{
		return Vector2D(v1.x - v2.x, v1.y - v2.y);
	}

	friend bool operator==(const Vector2D& v1, const Vector2D& v2)
	{
		return v1.x == v2.x && v1.y == v2.y;
	}

	void Normalize();
	static float Distance(const Vector2D& v1, const Vector2D& v2);
	static float DistanceSquare(const Vector2D& v1, const Vector2D& v2);
};

struct Transform2D
{
	Vector2D position;
	float rotation;
	float scale;

	static Transform2D ZeroTransform;

	Transform2D();
	Transform2D(float pos_x, float pos_y, float rotation, float scale);
	Transform2D(Vector2D position, float rotation, float scale);
};

struct RGBColor
{
	float R, G, B;

	static RGBColor White;
	static RGBColor Red;
	static RGBColor Green;
	static RGBColor Blue;
	static RGBColor Orange;
	static RGBColor Cyan;
	static RGBColor Pink;

	RGBColor();
	RGBColor(float r, float g, float b);
};

// some basic helper functions
class HelperFunctions
{
public:
	template<typename Z, typename T>
	inline static Z* cast(T* ptr) {
		return dynamic_cast<Z*>(ptr);
	}

	template<typename Base, typename T>
	inline static bool instanceof(T* ptr) {
		return dynamic_cast<Base*>(ptr) != nullptr;
	}

	template<typename T>
	inline static bool contains(const std::vector<T*>& vector, T* ptr) {
		auto it = std::find(vector.begin(), vector.end(), ptr);
		return (it != vector.end());
	}

	template<typename T>
	inline static void remove(std::vector<T*>& vector, T* ptr) {
		vector.erase(std::remove(vector.begin(), vector.end(), ptr), vector.end());
	}

	template<typename T>
	inline static void append(std::vector<T*>& vector, std::vector<T*> vectorToAdd) {
		if (vectorToAdd.size() > 0)
		{
			vector.insert(vector.end(), vectorToAdd.begin(), vectorToAdd.end());
		}
	}

	static Vector2D GetRandomPositionInRange(int maxX, int maxY);
};

// DELEGATES
struct DelegateHandle
{
public:
	DelegateHandle() : m_owner(nullptr), m_id(0) {}

private:
	DelegateHandle(const void* owner, uint64_t id)
		: m_owner(owner)
		, m_id(id)
	{}

	struct Hash
	{
		std::size_t operator()(const DelegateHandle& s) const noexcept
		{
			return std::hash<uint64_t>{}(s.m_id);
		}
	};

	friend bool operator==(const DelegateHandle& lhs, const DelegateHandle& rhs)
	{
		return lhs.m_id == rhs.m_id;
	}

	DelegateHandle& operator++()
	{
		++m_id;
		return *this;
	}

private:
	const void* m_owner;
	uint64_t m_id = 0;

	template<typename ...Args>
	friend struct Delegate;
};

template<typename ...Args>
struct Delegate
{
	using FuncType = std::function<void(Args...)>;

	void Broadcast(Args... args)
	{
		for (auto pair : m_OnInvokedFuncs)
		{
			auto func = pair.second;
			if (func != nullptr)
			{
				func(args...);
			}
		}
	}

	void operator()(Args... args)
	{
		Broadcast();
	}

	DelegateHandle Subscribe(FuncType callback)
	{
		DelegateHandle handle = ++m_count;
		m_OnInvokedFuncs[handle] = callback;

		return handle;
	}

	template<typename T>
	DelegateHandle Subscribe(T* obj, void(T::* callback)(Args...))
	{
		auto lambda = [obj, callback](Args... args) -> void
			{
				(obj->*callback)(args...); // calls the "callback" member function from a given "obj" object
			};

		DelegateHandle handle = ++m_count;
		m_OnInvokedFuncs[handle] = lambda;

		return handle;
	}

	void Unsubscribe(DelegateHandle handle)
	{
		if (handle.m_owner != this) return;

		auto it = m_OnInvokedFuncs.find(handle);
		if (it != m_OnInvokedFuncs.end())
		{
			m_OnInvokedFuncs.erase(it);
		}
	}

private:
	std::unordered_map<DelegateHandle, FuncType, DelegateHandle::Hash> m_OnInvokedFuncs;
	DelegateHandle m_count = { this, 0 };
};