// bv.h — Bit Vector interface
// Author: Prof. Darrell Long

# ifndef _BVector
# define _BVector
# include <stdint.h>

typedef struct bitV {
	uint8_t *vector;
	uint64_t length;
} bitV;

bitV *newVec(uint64_t);

void delVec(bitV *);

void oneVec(bitV *);

void setBit(bitV *, uint64_t);

void clrBit(bitV *, uint64_t);

uint8_t valBit(bitV *, uint64_t);

uint64_t lenVec(bitV *);
# endif
