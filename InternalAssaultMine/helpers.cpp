#include "pch.h"
#include "helpers.h"

uintptr_t helpers::findDMA(uintptr_t ptr, std::vector<unsigned int> offsets) {
	uintptr_t address = ptr;

	for (unsigned int i = 0; i < offsets.size(); i++) {
		address = *(uintptr_t*)address + offsets[i];
	}

	return address;
}
