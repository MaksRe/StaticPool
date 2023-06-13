#ifndef TEST_TYPE_H
#define TEST_TYPE_H

	#include "stdint.h"

	struct TestType_s {
		uint8_t v8;
		uint16_t v16;
		uint32_t v32;
	};

	typedef struct TestType_s TestType_t, *TestTypePtr_t;

	#define GenRandomTestValue(i) {(i + 1) % sizeof(uint8_t),  \
								   (i + 2) % sizeof(uint16_t), \
								   (i + 3) % sizeof(uint32_t)}

#endif
