#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-irseeker-v2.h"

tMUXSensor left, right;

void setupIRSmux(tMUXSensor one, tMUXSensor two) {
	left = one; right = two;
}

int findIRColumn() {
	return (HTIRS2readACDir(left) == 9 ? 3 :
				(HTIRS2readACDir(right) == 1 ? 1 : 2));
}
