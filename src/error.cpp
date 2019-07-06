#include "error.hpp"


namespace dainty
{

Error::Error(const char * message) :
    std::runtime_error{message}
{
};

}
