#include <thread>
#include <functional>
#include "order_service.h"
#include "logger.h"

using order_t = ns::order_t;

const size_t max_thread_count = 5;

order_service::order_service():
    _ctx(1),
    _frontend( _ctx, ZMQ_ROUTER ),
    _proxy_soc( _ctx, ZMQ_DEALER )
{
    _receivers.reserve( max_thread_count );
}

order_service::~order_service()
{
}
void order_service::run()
{
    auto recv_thr = std::thread( [ & ] ()
        {
            _frontend.bind( "tcp://*:5570" );
            _proxy_soc.bind( "inproc://order_receiver" );

            spdlog_w::info( "order_service accept on socket addr: tcp://*:5570" );
            spdlog_w::info( "receivers listen on socket addr: inproc://order_receiver" );

            for ( int i = 0; i < max_thread_count; ++i )
            {
                auto place_order = std::bind( &order_manager::place_order, &_manager, std::placeholders::_1 );
                auto& receiver = _receivers.emplace_back( _ctx, ZMQ_DEALER, place_order );
                std::thread th( &order_receiver::receive, &receiver );
                th.detach();
            }

            try
            {
                zmq::proxy( static_cast< void* >( _frontend ),
                            static_cast< void* >( _proxy_soc ),
                            nullptr );
            }
            catch ( std::exception& e )
            {}

            spdlog_w::info( "order_service has been started" );
        } );

    //std::thread process_thr( []()
    //                         {
    //                             //while ( true )
    //                             //{
    //                             //    _manager.process_orders();
    //                             //}
    //                         });

    //std::thread send_thr( []()
    //                      {
    //                          //zmqpp::message message;

    //                          //message << 
    //                          //socket.send( "World" );
    //                      });

    recv_thr.join();
}


int main( int argc, char* argv[] )
{
    order_service broker;
    broker.run();
    
    return 0;
}
