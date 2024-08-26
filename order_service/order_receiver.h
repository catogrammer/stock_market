#pragma once

#include <functional>
#include <zmq.hpp>

#include "order_manager.h"

using order_t = ns::order_t;

using place_order_functor = std::function<void( order_t )>;

class order_receiver
{
public:
    order_receiver( zmq::context_t& ctx,
                    int sock_type,
                    place_order_functor f )
        : _ctx( ctx ),
        _receiver_soc( _ctx, sock_type ),
        _order_functor( f )
    {
    }

    void receive();

private:
    zmq::context_t& _ctx;
    zmq::socket_t _receiver_soc;
    place_order_functor _order_functor;
};