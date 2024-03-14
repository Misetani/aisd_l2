#ifndef ARRAY_EXCEPTION
#define ARRAY_EXCEPTION
#include <string>

class Array_exception {
private:
    std::string m_error;
public:
    Array_exception(std::string error) : m_error{ error } {}
    const char* get_error() const { return m_error.c_str(); }
};
#endif