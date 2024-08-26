#include "order_receiver.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

void order_receiver::receive()
{
    _receiver_soc.connect( "inproc://order_receiver" );

    try
    {
        while ( true )
        {

            zmq::message_t identity;
            zmq::message_t message;
            auto rc = _receiver_soc.recv( &identity );
            if ( !rc )
                continue;

            rc = _receiver_soc.recv( &message );
            if ( !rc )
                continue;


            //const auto rc = _receiver_soc.recv( message );
            //if ( !rc )
            //    continue;

            //auto text = message.to_string();

            //auto j_o = json::parse( text );

            //order_t o = j_o;

            int parsed_num1 = 0;
            int parsed_num2 = 0;

            // Use a istringstream to parse the hexadecimal values
            std::istringstream hex_stream( identity.to_string() );
            hex_stream >> std::hex >> parsed_num1; // Extract the first hex number
            hex_stream.ignore( 1, '-' );             // Ignore the '-' separator
            hex_stream >> std::hex >> parsed_num2;

            order_t o;
            o._uuid = parsed_num1;
            o._id = parsed_num2;

            _order_functor( o );

            zmq::message_t replay_identity;
            replay_identity.copy( identity );

            std::string buf = "Order "+ identity.to_string() + "is placed";
            zmq::message_t replay( buf );

            _receiver_soc.send( replay_identity );
            _receiver_soc.send( replay );
        }
    }
    catch ( std::exception& e ) {}
}