/**
 * @file main.cpp
 * @author yao
 * @brief 
 * @version 0.5
 * @date 2025-12-09
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include "Language.h"
#include "util.h"
#include "main.h"
#include "Parser.h"
#include "Language.h"
using std::string;
using std::vector;
namespace fs = std::filesystem;
using std::cout,std::endl;

// std::unordered_set<std::string> SetExt = {
//     ".java",".JAVA",".py",".c",".cpp",".C",".cxx",".h",".hpp",".m",".js",".ts",".xml",".json",".txt"
// };
// std::unordered_set<std::string> las;//使用到了哪些编程语言，都放入这个哈希集合中
std::unordered_map<std::string,Language> lans;//使用到了哪些语言，都放到这个map,key---编程语言的名字，value---Language类

int main(void){
    std::vector<fs::path> ListFiles;
    // std::unordered_map<std::string,Language> Map;
    // MapInit(Map);
    setInit();
    fs::path cur = fs::current_path();
    // cout<<"cur = "<<cur<<endl;
    ListFiles = GetAllFiles(cur);
    for(auto& p:ListFiles){
        Parser tmp(p);
        tmp.ParseAll();
        if(tmp.file.Getis_program()){
            std::string tmp_name = tmp.file.Getname_program();
            if(lans.find(tmp_name) == lans.end()){
                lans.emplace(tmp_name,Language(tmp_name));
            }
            lans[tmp_name].addCodes(tmp.file.Getlines_code());
            lans[tmp_name].addNotes(tmp.file.Getlines_note());
            lans[tmp_name].addEmpty(tmp.file.Getlines_empty());
            lans[tmp_name].addFile();
        }
    }
    PrintAllInformation(lans);
    return 0;
}


/**
 * @brief 初始化Map
 * 
 * @param Map ，键值分别为string，这里的string为编程语言的名字,Language,这里的Language为自定义的类
 */
// void MapInit(std::unordered_map<std::string,Language>& Map){
//     vector<std::string> vecName = {"java","python","c_cpp","Matlab","JavaScript","TypeScript","Configuration","CMake"};
//     for(const auto& item:vecName){
//         // Map.insert(std::pair<std::string,Language>(item,Language(item)));
//         Map.insert(std::make_pair(item,Language(item)));
//     }
//     Map["java"].setExtensionSet(std::vector<std::string>{".java",".JAVA"});
//     Map["python"].setExtensionSet(std::vector<std::string>{".py",".PY"});
//     Map["c_cpp"].setExtensionSet(std::vector<std::string>{".c",".cpp",".C",".cxx",".h",".hpp"});
//     Map["Matlab"].setExtensionSet(".m");
//     Map["JavaScript"].setExtensionSet(".js");
//     Map["TypeScript"].setExtensionSet(".ts");
//     Map["Configuration"].setExtensionSet(std::vector<std::string>{".xml",".json"});
//     Map["CMake"].setExtensionSet(".txt");
// }
/**
 * @brief 打印输出所有信息
 * 
 * @param Map 
 */
void PrintAllInformation(const std::unordered_map<std::string,Language>& Map){
    cout<<"Language\t"<<"file\t"<<"code\t"<<"note\t"<<"empty"<<endl;
    for(const auto& item:Map){
        if(item.second.getFiles() == 0){
            continue;
        }
        cout<<item.second.getName()<<"\t\t"<<item.second.getFiles()<<"\t"<<item.second.getCodes()<<"\t"<<item.second.getNotes()<<"\t"<<item.second.getEmpty()<<endl;
    }
}
