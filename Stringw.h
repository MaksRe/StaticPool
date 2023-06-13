/**
 * @file Stringw.h
 * @brief Обертка модуля String.h
 * @details Обертка модуля string.h с добавлением функции memcpy_s в случае определения макроса _CRT_MEMORY_DEFINED
 *
 */

#ifndef STRINGW_H
#define STRINGW_H

    #include "string.h"

    #ifndef _CRT_MEMORY_DEFINED

        void *memcpy_s(void *_dest, size_t _numberOfElements, const void *_src, size_t _count);

    #endif

#endif
