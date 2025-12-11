#pragma once
#include <vector>
#include <map>
#include <filesystem>
#include <string>
#include <unordered_set>
#include <unordered_map>
namespace fs = std::filesystem;
/**
 * setC         C风格家族，     C, C++, C#, Java, JavaScript, TypeScript, Swift, Rust, Go, PHP
 * setScript    脚本语言家族    Python, Ruby, Bash, PowerShell, Perl, YAML, Makefile
 * setMark      标记语言家族    HTML, XML, Markdown, LaTeX, INI, TOML
 * setFUnc      函数语言家族    Haskell, OCaml, F#, Erlang, Elixir, Lisp, Scheme
 */
extern std::unordered_set<std::string> setC,setScript,setMark,setFunc;
extern const std::unordered_map<std::string,std::string> map_ext_program;
typedef enum State{
    Normal,//普通代码或者单行注释
    More,//多行注释
}state;


void setInit();

std::vector<fs::path> GetAllFiles(const fs::path& path);
void GetLinesOfFile(const fs::path& path,int& code,int& note,int& empty,const std::string& language);


void ParserCC(const fs::path& path,int& code,int& note,int& empty);
void ParserPyPy(const fs::path& path,int& code,int& note,int& empty);
void eraseSpaceFront(std::string& str);