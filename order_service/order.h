#pragma once

#include <string>

enum order_type
{
    buy,
    sell
};

#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace ns
{
    struct order_t
    {
        int _uuid;
        int _id;
        int _type;
        double _price;
        double _amount;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE( order_t, _uuid, _id, _type, _price, _amount )
}