#ifndef HOME_MANAGER_HPP
#define HOME_MANAGER_HPP

#include "config_manager.hpp"
#include "resources_manager.hpp"

class HomeManager:public Manager<HomeManager>
{
    friend class Manager<HomeManager>;

public:
    double get_current_hp_num();

    void decrease_hp(double val);

protected:
    HomeManager();
    ~HomeManager() = default;

private:
    double num_hp = 0;
};

#endif // HOME_MANAGER_HPP