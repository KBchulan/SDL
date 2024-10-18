#ifndef COIN_MANAGER_HPP
#define COIM_MANAGER_HPP

#include "coin_prop.hpp"
#include "config_manager.hpp"

class CoinManager : public Manager<CoinManager>
{
    friend class Manager<CoinManager>;

public:
    typedef std::vector<CoinProp *> CoinPropList;

public:
    void increase_coin(double val);

    void decrease_coin(double val);

    void on_update(double delta);

    void on_render(SDL_Renderer *renderer);

    double get_current_coin_num();

    CoinPropList &get_coin_prop_list();

    void spawn_coin_prop(const Vector2 &position);

protected:
    CoinManager();
    ~CoinManager();

private:
    double num_coin = 0;
    CoinPropList coin_prop_list;
};

#endif // COIN_MANAGER_HPP