#include "Collision.h"
#include "iostream"

CS230::CubeCollision::CubeCollision(Math::icube boundary, GameObject* object) :
    boundary(boundary),
    object(object)
{ }

Math::cube CS230::CubeCollision::WorldBoundary() {
    std::cout << object ->GetPosition().x<< std::endl;
    return {
        object->GetMatrix() * static_cast<Math::vec3>(boundary.point_1),
        object->GetMatrix() * static_cast<Math::vec3>(boundary.point_2),
    };
}
void CS230::CubeCollision::Draw(Math::TransformationMatrix display_matrix) {

    const double render_height = rlGetFramebufferHeight();

    Math::cube world_boundary = WorldBoundary();
    Math::vec3 bottom_left = display_matrix * Math::vec3{ world_boundary.Left(), world_boundary.Bottom(), world_boundary.Low() };
    Math::vec3 bottom_right = display_matrix * Math::vec3{ world_boundary.Right(), world_boundary.Bottom(), world_boundary.Low() };
    Math::vec3 top_left = display_matrix * Math::vec3{ world_boundary.Left(), world_boundary.Top(), world_boundary.Low() };
    Math::vec3 top_right = display_matrix * Math::vec3{ world_boundary.Right(), world_boundary.Top(), world_boundary.Low() };

    Math::vec3 high_left = display_matrix * Math::vec3{ world_boundary.Left(), world_boundary.Top(), world_boundary.High() };
    Math::vec3 high_right = display_matrix * Math::vec3{ world_boundary.Right(), world_boundary.Top(), world_boundary.High() };
    Math::vec3 low_left = display_matrix * Math::vec3{ world_boundary.Left(), world_boundary.Bottom(), world_boundary.High() };
    Math::vec3 low_right = display_matrix * Math::vec3{ world_boundary.Right(), world_boundary.Bottom(), world_boundary.High() };


    bottom_left.y = bottom_left.y * -1 + render_height;
    bottom_right.y = bottom_right.y * -1 + render_height;
    top_left.y = top_left.y * -1 + render_height;
    top_right.y = top_right.y * -1 + render_height;

    high_left.y = high_left.y * -1 + render_height;
    high_right.y = high_right.y * -1 + render_height;
    low_left.y = low_left.y * -1 + render_height;
    low_right.y = low_right.y * -1 + render_height;

    DrawLine(int(top_left.x), int(top_left.y), int(top_right.x), int(top_right.y), WHITE);
    DrawLine(int(bottom_right.x), int(bottom_right.y), int(top_right.x), int(top_right.y), WHITE);
    DrawLine(int(bottom_right.x), int(bottom_right.y), int(bottom_left.x), int(bottom_left.y), WHITE);
    DrawLine(int(top_left.x), int(top_left.y), int(bottom_left.x), int(bottom_left.y), WHITE);
}

bool CS230::CubeCollision::IsCollidingWith(GameObject* other_object) {
    Collision* other_collider = other_object->GetGOComponent<Collision>();

    if (other_collider == nullptr) {
        Engine::GetLogger().LogError("No collision component found");
        return false;
    }

    Math::cube cube_1 = WorldBoundary();
    Math::cube cube_2 = dynamic_cast<CubeCollision*>(other_collider)->WorldBoundary();


    if (!(cube_1.Right() < cube_2.Left() || cube_1.Left() > cube_2.Right() || cube_1.Top() < cube_2.Bottom() || cube_1.Bottom() > cube_2.Top() || cube_1.High() < cube_2.Low() || cube_1.Low() > cube_2.High())) {
        return true; 
    }
    return false; 

}
