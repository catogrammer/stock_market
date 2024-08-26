#include "service_base.h"
#include "logger.h"

service::service()
    : ctx_( 1 ),
     _socket( ctx_, zmq::socket_type::dealer )
{
}

service::~service()
{
}

void service::run()
{
    const auto identity = get_identity();
    _socket.set( zmq::sockopt::routing_id, identity );
    _socket.connect( "tcp://localhost:5570" );

    spdlog_w::info("clinet connected to server on addr: tcp://localhost:5570");

    zmq::pollitem_t items[] = {
        { _socket, 0, ZMQ_POLLIN, 0 } };
    int request_nbr = 0;
    try
    {
        while ( true )
        {
            for ( int i = 0; i < 100; ++i )
            {
                auto time_out = std::chrono::milliseconds(10);
                zmq::poll( items, 1, time_out );
                if ( items[ 0 ].revents & ZMQ_POLLIN )
                {
                    spdlog_w::info( "id: ", identity );
                    //std::cout << "id: " << identity << std::endl;
                    zmq::message_t response;
                    const auto rc = _socket.recv( response );
                    if ( !rc )
                        continue;

                    //std::cout << "Received " << response.to_string() << std::endl;
                    spdlog_w::info( "Received ", response.to_string() );
                }
            }

            std::string buf = "request #" + std::to_string( ++request_nbr );
            zmq::message_t request( buf );
            _socket.send( request );
        }
    }
    catch ( std::exception& e ) {}

    //// open the connection
    //cout << "Connecting to hello world server…" << endl;
    //socket.connect( endpoint );

    //int request_nbr;
    //for ( request_nbr = 0; request_nbr != 10; request_nbr++ )
    //{
    //    // send a message
    //    cout << "Sending Hello " << request_nbr << "…" << endl;
    //    zmqpp::message message;
    //    // compose a message from a string and a number
    //    message << "Hello";
    //    socket.send( message );
    //    string buffer;
    //    socket.receive( buffer );

    //    cout << "Received World " << request_nbr << endl;
    //}
}


int main( int argc, char* argv[] )
{
    service s;
    s.run();

    return 0;
}
