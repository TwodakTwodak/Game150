#include "FileIO.h"
#include "Engine.h"

FileObject arr[100];
int object_number = 0;

void FileInput(const std::filesystem::path& sprite_file) {
    if (sprite_file.extension() != ".txt") {
        throw std::runtime_error(sprite_file.generic_string() + " is not a .txt file");
    }
    std::ifstream in_file(sprite_file);

    if (in_file.is_open() == false) {
        throw std::runtime_error("Failed to load " + sprite_file.generic_string());
    }

    std::string text;
    in_file >> text;

    while (in_file.eof() == false) {
        if (text == "Number") {
            in_file >> object_number;
            arr[object_number - 1].Number = object_number;
        }
        else if (text == "Room") {
            int room_num;
            in_file >> room_num;
            arr[object_number - 1].Room = room_num;
        }
        else if (text == "Type") {
            std::string get_type;
            in_file >> get_type;
            arr[object_number - 1].Type = get_type;
        }
        else if (text == "Position") {
            double position_x, position_y, position_z;
            in_file >> position_x;
            in_file >> position_y;
            in_file >> position_z;
            arr[object_number - 1].Position = { position_x, position_y, position_z };
        }
        else if (text == "Information") {
            std::string get_information;
            in_file >> get_information;
            arr[object_number - 1].Information = get_information;
        }
        else if (text == "Size") {
            double size_x, size_y, size_z;
            in_file >> size_x;
            in_file >> size_y;
            in_file >> size_z;
            arr[object_number - 1].Size = { size_x, size_y, size_z };
        }
        else {
            Engine::GetLogger().LogError("Unknown command: " + text);
        }
        in_file >> text;
    }
}

void FileOutput(const std::filesystem::path& sprite_file)
{
    if(sprite_file.extension() != ".txt") {
        throw std::runtime_error(sprite_file.generic_string() + " is not a .txt file");
    }
    std::ofstream out_file(sprite_file);

    if (out_file.is_open() == false) {
        throw std::runtime_error("Failed to load " + sprite_file.generic_string());
    }

    for (int i = 0; i < 3; i++)
    {
        out_file << "Number ";
        out_file << arr[i].Number;
        out_file << '\n';
        out_file << "Room ";
        out_file << arr[i].Room;
        out_file << '\n';
        out_file << "Type ";
        out_file << arr[i].Type;
        out_file << '\n';
        out_file << "Position ";
        out_file << arr[i].Position.x;
        out_file << ' ';
        out_file << arr[i].Position.y;
        out_file << ' ';
        out_file << arr[i].Position.z;
        out_file << '\n';
        out_file << "Information ";
        out_file << arr[i].Information;
        out_file << '\n';
        out_file << "Size ";
        out_file << arr[i].Size.x;
        out_file << ' ';
        out_file << arr[i].Size.y;
        out_file << ' ';
        out_file << arr[i].Size.z;
        out_file << '\n';
    }
}
int GetRoom(int number)
{
    return arr[number].Room;
}
std::string GetType(int number)
{
    return arr[number].Type;
}
Math::vec3 GetPosition(int number)
{
    return arr[number].Position;
}
std::string GetInformation(int number)
{
    return arr[number].Information;
}
Math::vec3 GetSize(int number)
{
    return arr[number].Size;
}