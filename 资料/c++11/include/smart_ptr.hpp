#ifndef SMART_PTR_HPP
#define SMART_PTR_HPP

// 智能指针知识点比较少，大多在于应用，此处我给出一个单例的实现

#include <mutex>
#include <memory>

template <typename T>
class SmartPtr {
public:
    virtual ~SmartPtr() = default;

    static std::shared_ptr<T> GetInstance()
    {
        static std::once_flag flag;
        std::call_once(flag,[&]() {
            instance = std::shared_ptr<T>(new T);
        });
        return instance;
    }

private:
    inline static std::shared_ptr<T> instance = nullptr;

protected:
    SmartPtr() = default;
    explicit SmartPtr(const SmartPtr<T> &) = delete;
    SmartPtr &operator=(const SmartPtr<T> &) = delete;

};


#endif //SMART_PTR_HPP
