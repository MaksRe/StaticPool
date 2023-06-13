
/**
 * @file Pool.h
 * @brief interface for interaction and management of the allocated memory area.
 *
 */

#ifndef POOL_H
#define POOL_H

    #include "stdint.h"
    #include "stdbool.h"

    #ifdef __cplusplus
        extern "C" {
    #endif

        typedef uint16_t NumOfItems_t;
        typedef uint16_t ItemSize_t;
        typedef uint16_t ItemIndex_t;
        typedef struct Item_s Item_t, *ItemPtr_t;
        typedef struct Pool_s Pool_t, *PoolPtr_t, *const PoolConstPtr_t;

        /**
         * @brief               Fixed-length pool initialization numOfItems*itemSize.
         * @param pool          Pool object pointer.
         * @param numOfItems    Number of items in the pool.
         * @param itemSize      Item size of each element in the pool, in bytes.
         * @return              True: Pool created successfully.
         */
        bool Pool_Init(PoolConstPtr_t pool, NumOfItems_t numOfItems, ItemSize_t itemSize);

        /**
         * @brief       Get the index of a free element
         * @param pool  Pool object pointer
         * @return      free element index, otherwise -1
         */
        int8_t Pool_GetFreeItem(PoolConstPtr_t pool);

        /**
         * @brief       Get a pointer to the pool element by index.
         * @param pool  Pool object pointer
         * @param index Item index in pool
         * @return      Pointer to pool element
         */
        static inline void *Pool_GetItem(PoolConstPtr_t pool, ItemIndex_t index)
        {
            return (index >= pool->numOfItems) 
                ? NULL
                : pool->items + index * pool->itemSize;
        }

        /**
         * @brief       Release an element in the pool
         * @param pool  Pool object pointer
         * @param index Item Index
         */
        static inline void Pool_ReleaseItem(PoolConstPtr_t pool, uint8_t index)
        {
            if (index >= pool->numOfItems)
                return;

            ((ItemPtr_t)Pool_GetItem(&pool, index))->occupied = 0;
        }

        /**
         * @brief       Take a pool item.
         * @param pool  Pool object pointer
         * @param index Item Index
         */
        static inline void Pool_TakeItem(PoolConstPtr_t pool, uint8_t index)
        {
            if (index >= pool->numOfItems)
                return;

            ((ItemPtr_t)Pool_GetItem(&pool, index))->occupied = 1;
        }

        /**
         * @brief       Is item occupied?
         * @param pool  Pool object pointer
         * @param index Item Index
         * @return      True: occupied, otherwise free.
         */
        static inline bool Pool_IsItemOccupied(PoolConstPtr_t pool, uint8_t index)
        {
            return (bool)(((ItemPtr_t)Pool_GetItem(&pool, index))->occupied);
        }

        /**
         * @brief Fill the free sector of the data pool with the size src found 
         *        in the initial array of sectors and no more than pool->size bytes.
         *
         * @param pool  Pool object pointer
         * @param dst   Pointer to data source.
         * @param size  Data size in bytes.
         * @return      Occupied Item Index.
         *              -1: failed to get free element.
         *              -2: size exceeds allowable value.
         */
        int8_t Pool_Fill(PoolConstPtr_t pool, const void *const src, ItemSize_t size);


        /**
         * @brief       Deallocate memory and transfer to heap.
         *
         * @param pool  Pool object pointer
         */
        void Pool_Destroy(PoolConstPtr_t);

        /**
         * @brief       ....
         *
         * @param pool  Pool object pointer
         */
        static inline bool Pool_IsDestroyed(PoolConstPtr_t pool)
        {
            return (pool->item.ptr == NULL);
        }

    #ifdef __cplusplus
        }
    #endif

#endif
