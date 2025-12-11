#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief 存储单个文件信息的类，只做存储用，不进行处理
 * 
 */
class FileInformation{
private:
    fs::path path;
    bool is_program;
    std::string name_program;//编程语言的名字
    int lines_code;
    int lines_note;
    int lines_empty;
    double rate_note;
public:
    void __setpath(std::string path);
    void __setis_program(bool x);
    void __setname_program(std::string name);
    void __setlines_code(int code);
    void __setlines_note(int note);
    void __setlines_empty(int empty);
    void __setrate_note(double rate);

    fs::path Getpath();
    bool Getis_program();
    std::string Getname_program();
    int Getlines_code();
    int Getlines_note();
    int Getlines_empty();
    double Getrate_note();
};