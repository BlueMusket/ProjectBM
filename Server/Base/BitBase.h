#pragma once

#define BIT_TEST(VAR, INDEX) ((VAR & (INDEX)) != 0 )
#define BIT_SET( VAR, INDEX, VALUE ) VAR = VALUE ? VAR | INDEX : VAR & ~INDEX

#define BIT_SHIFT_TEST(VAR , INDEX) ((VAR & (1 << INDEX)) != 0)
#define BIT_SHIFT_SET(VAR, INDEX, VALUE) VAR = VALUE ? VAR | (1 << INDEX) : VAR & ~(1 << INDEX)