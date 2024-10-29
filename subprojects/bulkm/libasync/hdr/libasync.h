#pragma once

extern "C" {
/*!
 * \brief processorid идентификатор ковеера обработчиков данных
 */
typedef unsigned int processorid;

/*!
 * \brief метод connect создания нового конвейера обработчиков данных
 * \param blockSize размер блока данных, который будет отправлен в обработку
 * \return идентификатор созданного конвейера
 */
processorid connect(const unsigned int blockSize);

/*!
 * \brief метод recieve отправляет полученную команду в заранее созданный конвейер
 * \param processingId идентификатор ковейера обработки
 * \param pCommandBuffer символьный буффер, содержащий полученную команду
 * \param bufferSize размер символьного буффера команды
 */
void recieve(processorid processingId, const char* pCommandBuffer, unsigned int bufferSize);

/*!
 * \brief disconnect уничтожение конвейера по заданному идентификатору
 * \param processingId идентификатор ковейера, который будет уничтожен
 */
void disconnect(const int processingId);

}
