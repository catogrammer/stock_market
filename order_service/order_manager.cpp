#include "order_manager.h"

using order_t = ns::order_t;

void order_manager::place_order( order_t o )
{
    _orders.emplace_back( o );
}

void order_manager::cancel_order( const order_t& o )
{
    /*auto it = std::find( _orders.begin(), _orders.end(), o );
    if ( it == _orders.end() )
        return;

    _orders.erase( it );*/
}

void order_manager::process_orders()
{
    for ( const order_t& o : _orders )
    {
        //if ( o.is_complete() )
        //{
        //    cancel_order( o );
        //}
    }
}

void order_manager::dump( storage& st )
{
    st.store();
}