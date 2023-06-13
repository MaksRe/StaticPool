#include "pch.h"
#include "StaticPool.h"

TEST(StaticPool, Getting_1_Item)
{
	StaticPool_Init();

	ItemIndex_t index = StaticPool_GetFreeIndex();
	EXPECT_NE(index, -1);

	StaticPool_Result_e result = StaticPool_TakeItem(index);
	EXPECT_EQ(result, ITEM_SUCCESSFULLY_TAKEN);

	result = StaticPool_ReleaseItem(index);
	EXPECT_EQ(result, ITEM_SUCCESSFULLY_RELEASED);
}

TEST(StaticPool, Getting_All_Items)
{
	StaticPool_Init();

	for (ItemIndex_t i = 0; i < NUMBER_OF_ITEMS; i++)
	{
		ItemIndex_t index = StaticPool_GetFreeIndex();
		EXPECT_NE(index, -1);

		StaticPool_Result_e result = StaticPool_TakeItem(index);
		EXPECT_EQ(result, ITEM_SUCCESSFULLY_TAKEN);
	}

	for (ItemIndex_t i = 0; i < NUMBER_OF_ITEMS; i++)
	{
		StaticPool_Result_e result = StaticPool_ReleaseItem(i);
		EXPECT_EQ(result, ITEM_SUCCESSFULLY_RELEASED);
	}
}

TEST(StaticPool, All_Take)
{
	StaticPool_Init();

	for (ItemIndex_t i = 0; i < NUMBER_OF_ITEMS; i++)
	{
		ItemIndex_t index = StaticPool_GetFreeIndex();
		EXPECT_NE(index, -1);

		StaticPool_Result_e result = StaticPool_TakeItem(index);
		EXPECT_EQ(result, ITEM_SUCCESSFULLY_TAKEN);
	}

	ItemIndex_t index = StaticPool_GetFreeIndex();
	EXPECT_EQ(index, -1);
}

TEST(StaticPool, Re_Take)
{
	StaticPool_Init();

	ItemIndex_t index = StaticPool_GetFreeIndex();
	EXPECT_NE(index, -1);

	StaticPool_Result_e result = StaticPool_TakeItem(index);
	EXPECT_EQ(result, ITEM_SUCCESSFULLY_TAKEN);

	result = StaticPool_TakeItem(index);
	EXPECT_EQ(result, ITEM_ALREADY_TAKEN);
}

TEST(StaticPool, Fill_Item)
{
	Item_t tmpItem = GenRandomTestValue(1);

	StaticPool_Init();

	ItemIndex_t index = StaticPool_GetFreeIndex();
	EXPECT_NE(index, -1);

	StaticPool_Result_e result = StaticPool_TakeItem(index);
	EXPECT_EQ(result, ITEM_SUCCESSFULLY_TAKEN);

	bool fillingResult = StaticPool_Fill(index, &tmpItem);
	EXPECT_EQ(fillingResult, true);

	ItemPtr_t itemPtr = StaticPool_GetItem(index);
	ASSERT_NE(itemPtr, nullptr);
	Item_t item = (Item_t)*itemPtr;

	int compareResult = memcmp(&tmpItem, &item, sizeof(Item_t));
	EXPECT_EQ(compareResult, 0);

	result = StaticPool_ReleaseItem(index);
	EXPECT_EQ(result, ITEM_SUCCESSFULLY_RELEASED);
}

TEST(StaticPool, Fill_All_Item)
{
	StaticPool_Init();

	for (ItemIndex_t i = 0; i < NUMBER_OF_ITEMS; i++)
	{
		Item_t tmpItem = GenRandomTestValue(i);

		ItemIndex_t index = StaticPool_GetFreeIndex();
		EXPECT_NE(index, -1);

		StaticPool_Result_e result = StaticPool_TakeItem(index);
		EXPECT_EQ(result, ITEM_SUCCESSFULLY_TAKEN);

		bool fillingResult = StaticPool_Fill(index, &tmpItem);
		EXPECT_EQ(fillingResult, true);

		ItemPtr_t itemPtr = StaticPool_GetItem(index);
		ASSERT_NE(itemPtr, nullptr);
		Item_t item = (Item_t)*itemPtr;

		int compareResult = memcmp(&tmpItem, &item, sizeof(Item_t));
		EXPECT_EQ(compareResult, 0);
	}

	for (ItemIndex_t i = 0; i < NUMBER_OF_ITEMS; i++)
	{
		StaticPool_Result_e result = StaticPool_ReleaseItem(i);
		EXPECT_EQ(result, ITEM_SUCCESSFULLY_RELEASED);
	}
}
