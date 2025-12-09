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
std::unordered_set<std::string> setC,setScript,setMark,setFunc;


static bool ShouldSkipDirectory(const fs::path& path);

static void ParserC(const fs::path& path,int& code,int& note,int& empty);
static void ParserPy(const fs::path& path,int& code,int& note,int& empty);

static void eraseSpaceFront(std::string& str);

void setInit(){
    //C, C++, C#, Java, JavaScript, TypeScript, Swift, Rust, Go, PHP
    setC = {"c_cpp","java","JavaScript","TypeScript"};
    //Python, Ruby, Bash, PowerShell, Perl, YAML, Makefile
    setScript = {"python"};
    //HTML, XML, Markdown, LaTeX, INI, TOML
    setMark = {"HTML"};
    //Haskell, OCaml, F#, Erlang, Elixir, Lisp, Scheme
    setFunc = {"Haskell"};
}

/**
 * @brief  获取一个文件的代码行数和注释行数
 * 
 * @param path 文件路径
 * @param code 代码行数
 * @param note 注释行数，目前为测试版，note恒为0，code则为code+note;
 */
void GetLinesOfFile(const fs::path& path,int& code,int& note,int& empty,const std::string& language){
    if(setC.find(language) != setC.end()){
        //证明是C语言风格的语言
        ParserC(path,code,note,empty);
    }else if(setScript.find(language) != setScript.end()){
        ParserPy(path,code,note,empty);
    }
    // while(std::getline(f,line)){
    //     if(line.empty()){
    //         empty++;
    //     }else{
    //         res++;
    //     }
    // }
    // code = res;
    // note = 0;
}   

static void ParserC(const fs::path& path,int& code,int& note,int& empty){
    std::ifstream f(path);
    int code_tmp = 0,note_tmp=0,empty_tmp=0;
    std::string line;
    state cur = Normal;
    while(std::getline(f,line)){
        if(line.empty()){
            empty_tmp++;
        }else{
            eraseSpaceFront(line);
            if(cur == More){
                if(line[1] == '/' && line[0] == '*'){
                    //多行注释结束的标志
                    cur = Normal;
                    note_tmp++;
                }else{
                    note_tmp++;
                }
            }else if(line[0] == line[1] && line[1] == '/'){
                //单行注释
                note_tmp++;
            }else if(line[0] == '/' && line[1] == '*'){
                //多行注释
                cur = More;
                note_tmp++;
            }else{
                //否则就是code
                code_tmp++;
            }
        }
    }
    code = code_tmp;
    note = note_tmp;
    empty = empty_tmp;
}
static void ParserPy(const fs::path& path,int& code,int& note,int& empty){
    std::ifstream f(path);
    int code_tmp = 0,note_tmp = 0,empty_tmp = 0;
    std::string line;
    state cur = Normal;
    while(std::getline(f,line)){
        if(line.empty()){
            empty_tmp++;
        }else{
            eraseSpaceFront(line);
            if(cur == More){
                if(line[2] == '\'' && line[1] == '\'' && line[0] == '\''){
                    //多行注释结束的标志
                    cur = Normal;
                    note_tmp++;
                }else{
                    note_tmp++;
                }
            }else if(line[0] == '#'){
                //单行注释
                note_tmp++;
            }else if(line[0] == '\'' && line[1] == '\'' && line[2] == '\''){
                //多行注释
                cur = More;
                note_tmp++;
            }else{
                //否则就是code
                code_tmp++;
            }
        }
    }
    code = code_tmp;
    note = note_tmp;
    empty = empty_tmp;
}

/**
 * @brief 去除参数str前面的空格，使得str第一个字符不是空格
 * 
 * @param str 
 */
static void eraseSpaceFront(std::string& str){
    str.erase(0,str.find_first_not_of(" "));
}

/**
 * @brief Get the All Files object
 * 
 * @param path 目录的路径
 * @return std::vector<fs::path> 所有的文件的路径
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

