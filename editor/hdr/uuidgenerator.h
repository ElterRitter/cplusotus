#pragma once
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace otuseditor {

namespace uuidgenerator
{
    static std::string makeID()
    {
        boost::uuids::uuid id;
        boost::uuids::random_generator gen;
        id = gen();
        return boost::uuids::to_string(id);
    }
};

};
