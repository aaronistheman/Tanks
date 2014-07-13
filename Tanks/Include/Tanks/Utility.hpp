#ifndef TANKS_UTILITY_HPP
#define TANKS_UTILITY_HPP

#include <sstream>

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

#include <Tanks/Utility.inl>
#endif // TANKS_UTILITY_HPP