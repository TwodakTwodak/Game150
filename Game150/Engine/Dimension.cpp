#include "Dimension.h"

Dimension current_dimension = Dimension::Top;

Dimension CurrentDimension::GetDimension() {
	return current_dimension;
}
void CurrentDimension::SetDimension(Dimension new_dimension) {
	current_dimension= new_dimension;
}

