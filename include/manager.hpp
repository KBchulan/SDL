#ifndef MANAGER_HPP
#define MANAGER_HPP

template <typename T>
class Manager
{
public:
	static T* instance()
	{
		if (!manager)
			manager = new T();
		return manager;
	}

private:
	inline static T* manager = nullptr;

protected:
	Manager() = default;
	~Manager() = default;
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;

};

#endif // !MANAGER_HPP
