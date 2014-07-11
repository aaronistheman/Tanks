#ifndef TANKS_STRINGHELPERS_HPP
#define TANKS_STRINGHELPERS_HPP

#include <sstream>

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

#include <Tanks/StringHelpers.inl>
#endif // TANKS_STRINGHELPERS_HPP
