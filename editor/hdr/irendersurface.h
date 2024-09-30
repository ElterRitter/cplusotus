#pragma once

#include "gotusdocument.h"

namespace otuseditor {

/*!
 * \brief Класс IRenderSurface определяет интерфейс контекста для рисования элементов
 */
class IRenderSurface
{
public:
    IRenderSurface() = default;
    virtual ~IRenderSurface() = default;

    /*!
     * \brief renderDocument задаёт документ, который будет рисоваться в контексте
     * \param document невладеющий указатель на документ, который нужно отрисовать
     */
    virtual void renderDocument(const GOtusDocument::WPtr &document) = 0;
};

};
