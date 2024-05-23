#include "Dimension.h"

Dimension current_dimension = Dimension::Side;

Dimension CurrentDimension::GetDimension() {
	return current_dimension;
}
void CurrentDimension::SetDimension(Dimension new_dimension) {
	current_dimension= new_dimension;
}

