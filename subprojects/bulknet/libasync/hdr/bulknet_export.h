#ifndef ASYNC_EXPORT_H
#define ASYNC_EXPORT_H

#ifdef WIN32
#ifndef ASYNC_BUILD_STATIC
    #ifdef ASYNC_LIBRARY
        #define ASYNC_EXPORT __declspec(dllexport)
    #else
        #define ASYNC_EXPORT __declspec(dllimport)
    #endif
#endif
#else   // UNIX
    #define ASYNC_EXPORT __attribute__((visibility ("default")))
#endif


#endif // ASYNC_EXPORT_H
