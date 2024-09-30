#pragma once

#include "gotusdocument.h"

namespace otuseditor {

class IRenderSurface
{
public:
    IRenderSurface() = default;
    virtual ~IRenderSurface() = default;

    virtual void renderDocument(const GOtusDocument::WPtr &document) = 0;
};

};
