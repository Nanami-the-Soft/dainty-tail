#pragma once

#include <stdexcept>


namespace dainty
{

class Error :
    public std::runtime_error
{
public:
    Error(const char *);
    virtual ~Error() = default;
};

}
