#include <string>
#include <iostream>


#include <iomanip>
#include <sstream>
#include <random>

#include "zmq.hpp"

int within( int upper_bound )
{
    static std::mt19937 generator( std::random_device{}( ) );
    std::uniform_int_distribution<int> distribution( 0, upper_bound - 1 );
    return distribution( generator );
}

// generate random identity
std::string get_identity()
{
    int num1 = within( 0x10000 );
    int num2 = within( 0x10000 );

    std::stringstream ss;
    ss << std::uppercase << std::setfill( '0' ) << std::setw( 4 ) << std::hex << num1 << '-'
        << std::setw( 4 ) << num2;

    return ss.str();
}

class service
{
public:
	service();
	~service();

    void run();
private:
    zmq::context_t ctx_;
    zmq::socket_t _socket;
};