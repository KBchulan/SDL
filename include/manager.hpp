#ifndef MANAGER_H
#define MANAGER_H

template <typename T>
class Manager
{
public:
    static T *instance()
    {
        if (!manager)
            manager = new T();
        return manager;
    }

private:
    static T *manager;

protected:
    Manager() = default;
    ~Manager() = default;
    Manager(const Manager &) = delete;
    Manager &operator=(const Manager &) = delete;
};

template <typename T>
T *Manager<T>::manager = nullptr;

#endif // MANAGER_H