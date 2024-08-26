#pragma once

#include <vector>
#include "order.h"

using order_t = ns::order_t;

class storage
{

public:
    void store() {};
};

class order_manager
{
    std::vector<order_t> _orders;

public:
    void place_order( order_t o );
    void cancel_order( const order_t& o );
    void process_orders();
    void dump( storage& st );
};
