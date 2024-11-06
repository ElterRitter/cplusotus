#pragma once
#include "bulknet_export.h"

extern "C" {
/*!
 * \brief processorid идентификатор ковеера обработчиков данных
 */
typedef unsigned int processorid;

/*!
 * \brief метод bulk_connect создания нового конвейера обработчиков данных
 * \param blockSize размер блока данных, который будет отправлен в обработку
 * \return идентификатор созданного конвейера
 */
ASYNC_EXPORT processorid bulk_connect(const unsigned int blockSize);

/*!
 * \brief метод bulk_recieve отправляет полученную команду в заранее созданный конвейер
 * \param processingId идентификатор ковейера обработки
 * \param pCommandBuffer символьный буффер, содержащий полученную команду
 * \param bufferSize размер символьного буффера команды
 */
ASYNC_EXPORT void bulk_recieve(processorid processingId, const char* pCommandBuffer, unsigned int bufferSize);

/*!
 * \brief метод bulk_disconnect уничтожение конвейера по заданному идентификатору
 * \param processingId идентификатор ковейера, который будет уничтожен
 */
ASYNC_EXPORT void bulk_disconnect(const int processingId);

}
