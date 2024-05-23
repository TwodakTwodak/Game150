#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include "Vec3.h"

struct FileObject {
	int Number;
	int Room;
	std::string Type;
	Math::vec3 Position;
	std::string Information;
	Math::vec3 Size;
};



void FileInput(const std::filesystem::path& sprite_file);
void FileOutput(const std::filesystem::path& sprite_file);
int GetRoom(int number);
std::string GetType(int number);
Math::vec3 GetPosition(int number);
std::string GetInformation(int number);
Math::vec3 GetSize(int number);
