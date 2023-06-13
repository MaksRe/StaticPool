/**
 * @file StaticPool.h
 * @brief Interface for interacting with a static memory pool.
 *
 * @details User has to change only two parameters: ITEM_TYPE and NUMBER_OF_ITEMS
 *          for properly configure static memory pool
 */

#ifndef STATIC_POOL_H
#define STATIC_POOL_H

    #include "stdint.h"
    #include "stdbool.h"

    #include "TestType.h"

    #ifdef __cplusplus
        extern "C" {
    #endif

        #define ITEM_TYPE           TestType_t ///< Type of stored items in pool (can be any custom type)
        #define NUMBER_OF_ITEMS     (1000)      ///< Number of items in pool

        #if (NUMBER_OF_ITEMS < INT8_MAX)
            typedef int8_t ItemIndex_t;
        #elif (NUMBER_OF_ITEMS < INT16_MAX)
            typedef int16_t ItemIndex_t;
        #elif (NUMBER_OF_ITEMS < INT32_MAX)
            typedef int32_t ItemIndex_t;
        #elif (NUMBER_OF_ITEMS < INT64_MAX)
            typedef int64_t ItemIndex_t;
        #else 
            #error Undefined ItemIndex_t
        #endif

        typedef enum {
            ITEM_SUCCESSFULLY_TAKEN     = 1,
            ITEM_SUCCESSFULLY_RELEASED  = 2,
            ITEM_INDEX_OUTSIDE          = -1,
            ITEM_ALREADY_TAKEN          = -2,
            ITEM_ALREADY_RELEASED       = -3,
        } StaticPool_Result_e;

        typedef ITEM_TYPE Item_t, *ItemPtr_t;

        /**
         * @brief Initialization static memory pool.
         */
        void StaticPool_Init(void);

        /**
         * @brief   Getting the index of free item of static pool.
         * @return  >= 0: index of free item, -1: no free items
         */
        ItemIndex_t StaticPool_GetFreeIndex();

        /**
         * @brief       Getting pointer to item by index
         * @param index index of item
         * @return      pointer to item
         */
        ItemPtr_t StaticPool_GetItem(ItemIndex_t index);

        /**
         * @brief       Take item by index
         * @param index index of item
         * @return      see StaticPool_Result_e
         */
        StaticPool_Result_e StaticPool_TakeItem(ItemIndex_t index);

        /**
         * @brief       Release occupied item by index
         * @param index Index of item
         * @return      see StaticPool_Result_e
         */
        StaticPool_Result_e StaticPool_ReleaseItem(ItemIndex_t index);

        /**
         * @brief           Copy srcItem to pool item by index
         * @param index     destination item index
         * @param srcItem   pointer to source item
         * @return          operation result
         */
        bool StaticPool_Fill(ItemIndex_t index, ItemPtr_t srcItem);

    #ifdef __cplusplus
        }
    #endif

#endif

