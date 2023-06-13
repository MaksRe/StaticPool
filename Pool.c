/**
 * @file Pool.c
 *
 */

#include "stdlib.h"
#include "Stringw.h"

#include "Pool.h"

struct Pool_s {
    uint8_t *items;             ///< Pointer to allocated memory
    uint8_t *mask;

    uint16_t maskSize;
    NumOfItems_t numOfItems;    ///< Number of items
    ItemSize_t itemSize;        ///< Size of one element (in bytes)
};

bool Pool_Init(PoolConstPtr_t pool, NumOfItems_t numOfItems, ItemSize_t itemSize)
{
    pool->items = (uint8_t *)calloc(numOfItems, itemSize);
    if (pool->items == NULL)
        return false;

    pool->maskSize = numOfItems / 8 + (uint8_t)(numOfItems % 8 > 0);
    pool->mask = (uint8_t *)malloc(pool->maskSize);
    if (pool->mask == NULL)
    {
        Pool_Destroy(&pool);

        return false;
    }

    /*
    if (numOfItems % 8 > 0)
        for ()
        pool->mask[numOfItems / 8] |= ~(numOfItems % 8)
        */

    pool->numOfItems = numOfItems;
    pool->itemSize = itemSize;

    return true;
}

int8_t Pool_GetFreeItem(PoolConstPtr_t pool)
{
    uint16_t i = 0;

    for (; i < pool->maskSize; i++)
    {
        uint8_t part = *(&pool->mask[i]);
        uint8_t cnt = 0;

        for (; part != 0; part >>= 1, cnt++)
            if (!(part & 1))
                return i * 8 + cnt;
    }

    return -1;
}

int8_t Pool_Fill(PoolConstPtr_t pool, const void *const src, ItemSize_t itemSize)
{
    int8_t index = Pool_GetFreeItem(pool);
    if (index == -1)
        return -1;

    if (itemSize > pool->itemSize)
        return -2;

    memcpy_s(Pool_GetItem(pool, index),
             itemSize,
             src,
             itemSize);

    Pool_TakeItem(pool, index);

    return index;
}

void Pool_Destroy(PoolConstPtr_t pool)
{
    if (pool->items == NULL &&
        pool->mask  == NULL)
        return;
    
    if (pool->items != NULL)
    {
        free(pool->items);
        pool->items = NULL;
    }

    if (pool->mask != NULL)
    {
        free(pool->mask);
        pool->mask = NULL;
    }

    pool->maskSize = 0;
    pool->numOfItems = 0;
    pool->itemSize = 0;
}
