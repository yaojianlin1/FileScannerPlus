#pragma once
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;


std::vector<fs::path> GetAllFiles(const fs::path& path);
void GetLinesOfFile(const fs::path& path,int code,int note);
