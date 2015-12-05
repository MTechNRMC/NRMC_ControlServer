#include <stdexcept>

class NotImplementedException : public std::logic_error
{
public:
    virtual char const * what() const { return "Function not yet implemented."; }
};