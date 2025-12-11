#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <filesystem>
#include "SingleFile.h"
#include "util.h"
namespace fs = std::filesystem;


/**
 * @brief 解析器工具类，只是一个工具
 * 通过将单个文件的路径输入，可以得到该文件的全部信息也就是FileInformation
 * 
 */
class Parser{
private:
    FileInformation file;

    void IsProgram();
    void Infor();

    void ParserC(int& code,int& note,int& empty);
    void ParserPy(int& code,int& note,int& empty);


public:
    Parser(fs::path p){
        //这里的p是单个文件的路径
        file.__setis_program(false);
        file.__setlines_code(0);
        file.__setlines_empty(0);
        file.__setlines_note(0);
        file.__setname_program("");
        file.__setpath(p.string());
        file.__setrate_note(0.0);
    }

    void ParseAll();
};