#pragma once

#include <iostream>

#include <zmq.hpp>

#include "order_manager.h"
#include "order_receiver.h"

class order_service
{
    zmq::context_t _ctx;
    zmq::socket_t _frontend;
    zmq::socket_t _proxy_soc;

    std::vector<order_receiver> _receivers;
    order_manager _manager;
public:
    order_service();
    ~order_service();

    void run();
};