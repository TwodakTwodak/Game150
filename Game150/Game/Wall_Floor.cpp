#include "Wall_Floor.h"

Wall_Floor::Wall_Floor(Math::vec3 start_position) : CS230::GameObject(start_position)
{
    collision_type = Block;
    side_sprite.Load("Assets/Side_wall_Floor.spt");
    top_sprite.Load("Assets/Top_Wall_Floor.spt");
}
Wall_Floor2::Wall_Floor2(Math::vec3 start_position) : CS230::GameObject(start_position)
{
    collision_type = Block;
    side_sprite.Load("Assets/Side_wall_Floor.spt");
    top_sprite.Load("Assets/Top_Wall_Floor2.spt");
}
