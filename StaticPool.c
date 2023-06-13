/**
 * @file StaticPool.c
 * @brief Implementation of a static memory pool.
 */

#include "stdlib.h"
#include "string.h"

#include "StaticPool.h"

#define ITEM_SIZE (sizeof(ITEM_TYPE))

#pragma pack(push, 1)
	typedef struct {
		uint8_t occupied : 1;
		ITEM_TYPE item;
	} PrivateItem_s;
#pragma pack(pop)

typedef PrivateItem_s PrivateItem_t, *PrivateItemPtr_t;

static PrivateItem_t pool[NUMBER_OF_ITEMS] = {0};

void StaticPool_Init(void)
{
	memset(&pool, 0, sizeof(pool));
}

static inline PrivateItemPtr_t StaticPool_GetPrivateItemByIndex(ItemIndex_t index)
{
	if (index >= NUMBER_OF_ITEMS)
		return NULL;

	return &pool[index];
}

ItemIndex_t StaticPool_GetFreeIndex()
{
	ItemIndex_t i = 0;

	for (; i < NUMBER_OF_ITEMS; i++)
		if (!StaticPool_GetPrivateItemByIndex(i)->occupied)
			return i;
	return -1;
}

ItemPtr_t StaticPool_GetItem(ItemIndex_t index)
{
	if (index >= NUMBER_OF_ITEMS)
		return NULL;
	
	return &(StaticPool_GetPrivateItemByIndex(index)->item);
}

StaticPool_Result_e StaticPool_TakeItem(ItemIndex_t index)
{
	if (index >= NUMBER_OF_ITEMS)
		return ITEM_INDEX_OUTSIDE;

	PrivateItemPtr_t privateItem = StaticPool_GetPrivateItemByIndex(index);
	if (privateItem->occupied)
		return ITEM_ALREADY_TAKEN;

	privateItem->occupied = 1;

	return ITEM_SUCCESSFULLY_TAKEN;
}

StaticPool_Result_e StaticPool_ReleaseItem(ItemIndex_t index)
{
	if (index >= NUMBER_OF_ITEMS)
		return ITEM_INDEX_OUTSIDE;

	PrivateItemPtr_t privateItem = StaticPool_GetPrivateItemByIndex(index);
	if (!privateItem->occupied)
		return ITEM_ALREADY_RELEASED;

	privateItem->occupied = 0;

	return ITEM_SUCCESSFULLY_RELEASED;
}

bool StaticPool_Fill(ItemIndex_t index, ItemPtr_t srcItem)
{
	ItemPtr_t itemPtr = StaticPool_GetItem(index);
	if (itemPtr == NULL)
		return false;

	memcpy_s(itemPtr,
			 ITEM_SIZE,
			 srcItem,
			 ITEM_SIZE);

	return true;
}

