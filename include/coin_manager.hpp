#ifndef COIN_MANAGER_HPP
#define COIM_MANAGER_HPP

#include "config_manager.hpp"

class CoinManager : public Manager<CoinManager>
{
    friend class Manager<CoinManager>;

public:
    void increase_coin(double val);

    void decrease_coin(double val);

protected:
    CoinManager();
    ~CoinManager();

private:
    double num_coin = 0;
};

#endif // COIN_MANAGER_HPP