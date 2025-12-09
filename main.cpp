#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "Language.h"
#include "util.h"
#include "main.h"
using std::string;
using std::vector;
namespace fs = std::filesystem;
using std::cout,std::endl;

std::unordered_set<std::string> SetExt = {
    ".java",".JAVA",".py",".PY",".c",".cpp",".C",".cxx",".h",".hpp",".m",".js",".ts",".xml",".json",".txt"
};
int main(void){
    std::vector<fs::path> ListFiles;
    std::unordered_map<std::string,Language> Map;
    MapInit(Map);
    fs::path cur = fs::current_path();
    // cout<<"cur = "<<cur<<endl;
    ListFiles = GetAllFiles(cur);
    for(const auto& item:ListFiles){
        std::string extTmp = item.filename().extension().string();
        std::string nameTmp = item.filename().string();
        // cout<<"extTmp:"<<extTmp<<"\t"<<"nameTmp:"<<nameTmp<<endl;
        if(SetExt.find(extTmp) != SetExt.end()){
            if(extTmp == ".txt" && nameTmp == "CMakeLists.txt"){
                Map["CMake"].addFiles();
                int code=0,note=0,empty=0;
                GetLinesOfFile(item,code,note,empty);
                Map["CMake"].addCodes(code);
                Map["CMake"].addNotes(note);
                Map["CMake"].addEmpty(empty);
            }else if(extTmp != ".txt"){
                int code=0,note=0,empty=0;
                GetLinesOfFile(item,code,note,empty);
                // cout<<"code:"<<code<<"\t"<<"note:"<<note<<endl;
                for(auto& it:Map){
                    if(it.second.IsBelongTo(extTmp)){
                        it.second.addFiles();
                        it.second.addCodes(code);
                        it.second.addNotes(note);
                        it.second.addEmpty(empty);
                    }
                }
            }
        }
    }
    PrintAllInformation(Map);
    return 0;
}
/**
 * @brief 初始化Map
 * 
 * @param Map ，键值分别为string,Language
 */
void MapInit(std::unordered_map<std::string,Language>& Map){
    vector<std::string> vecName = {"java","python","c_cpp","Matlab","JavaScript","TypeScript","Configuration","CMake"};
    for(const auto& item:vecName){
        // Map.insert(std::pair<std::string,Language>(item,Language(item)));
        Map.insert(std::make_pair(item,Language(item)));
    }
    Map["java"].setExtensionSet(std::vector<std::string>{".java",".JAVA"});
    Map["python"].setExtensionSet(std::vector<std::string>{".py",".PY"});
    Map["c_cpp"].setExtensionSet(std::vector<std::string>{".c",".cpp",".C",".cxx",".h",".hpp"});
    Map["Matlab"].setExtensionSet(".m");
    Map["JavaScript"].setExtensionSet(".js");
    Map["TypeScript"].setExtensionSet(".ts");
    Map["Configuration"].setExtensionSet(std::vector<std::string>{".xml",".json"});
    Map["CMake"].setExtensionSet(".txt");
}
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
