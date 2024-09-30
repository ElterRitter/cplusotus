#pragma once
#include <inttypes.h>

namespace otuseditor {

struct SimplePoint
{
    uint32_t x_;
    uint32_t y_;
    SimplePoint() : x_(0), y_(0) { };
    SimplePoint(const uint32_t x, const uint32_t y) : x_(x), y_(y) { };
};

};
