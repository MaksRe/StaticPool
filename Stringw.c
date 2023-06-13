/**
 *
 *
 *
 */

#include "Stringw.h"

#ifndef _CRT_MEMORY_DEFINED

    void *memcpy_s(void *_dest, size_t _numberOfElements, const void *_src, size_t _count)
    {
        if (_numberOfElements < _count)
            return NULL;

        return memcpy(_dest, _src, _count);
    }

#endif
