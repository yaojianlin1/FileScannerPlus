#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include "util.h"
std::unordered_set<std::string> set_skip_dir = {
    "build","obj","bin"
};
namespace fs = std::filesystem;
std::vector<fs::path> files;



static bool ShouldSkipDirectory(const fs::path& path);


/**
 * @brief  获取一个文件的代码行数和注释行数
 * 
 * @param path 文件路径
 * @param code 代码行数
 * @param note 注释行数，目前为测试版，note恒为0，code则为code+note;
 */
void GetLinesOfFile(const fs::path& path,int code,int note){
    std::ifstream f(path);
    int res = 0;
    std::string line;
    while(std::getline(f,line)){
        if(line.empty()){
            continue;
        }else{
            res++;
        }
    }
    code = res;
    note = 0;
}   

/**
 * @brief Get the All Files object
 * 
 * @param path 目录的路径
 * @return std::vector<fs::path> 
 */
std::vector<fs::path> GetAllFiles(const fs::path& path){
    if(!fs::exists(path)){
        return files;
    }
    fs::directory_iterator list(path);
    for(const auto& item : list){
        if(fs::is_directory(item) && !ShouldSkipDirectory(item.path())){
            GetAllFiles(item.path());
        }else if(fs::is_regular_file(item.path())){
            files.push_back(item.path());
        }
    }
    return files;
}
/**
 * @brief 判断是否应该跳过这个目录
 * 需要跳过的有：隐藏目录（即以.开头的目录）,build,obj,bin;
 * @param path 必须是directory
 * @return true 
 * @return false 
 */
static bool ShouldSkipDirectory(const fs::path& path){
    std::string dir_name = path.filename().string();
    if(dir_name[0] == '.'){
        return true;
    }
    if(set_skip_dir.find(dir_name) != set_skip_dir.end()){
        return true;
    }
    return false;
}