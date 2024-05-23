#pragma once

enum class Dimension {
    Side,
    Top
};
/*
class CurrentDimension {
public:
    Dimension GetDimension();
    void SetDimension(Dimension new_dimension);
private:
    Dimension current_dimension = Dimension::Side;
};*/

class CurrentDimension {
public:
    Dimension GetDimension();
    void SetDimension(Dimension new_dimension);
};
