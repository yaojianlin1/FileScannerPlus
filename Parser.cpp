#include "Parser.h"
#include "util.h"
#include <fstream>
namespace fs = std::filesystem;

static std::unordered_set<std::string> SetExt = {
    ".java",".JAVA",".py",".c",".cpp",".C",".cxx",".h",".hpp",".m",".js",".ts",".xml",".json",".txt"
};

/*==============================================================================================================*/

void Parser::IsProgram(){
    std::string ext = this->file.Getpath().filename().extension().string();
    std::string fn = this->file.Getpath().filename().string();
    if(SetExt.find(ext) == SetExt.end()){
        this->file.__setis_program(false);
    }else{
        if(ext == ".txt"){
            this->file.__setis_program(((fn == "CMakeLists.txt")?true:false));
        }else{
            this->file.__setis_program(true);
        }
    }
}

void Parser::Infor(){
    this->IsProgram();
    if(!this->file.Getis_program()){
        return;
    }
    std::string ext = this->file.Getpath().filename().extension().string();
    int code=0,note=0,empty=0;

    this->file.__setname_program(map_ext_program.at(ext));

    //c语言家族，script家族,mark家族，func家族
    if(setC.find(map_ext_program.at(ext)) != setC.end()){
        this->ParserC(code,note,empty);
    }else if(setScript.find(map_ext_program.at(ext)) != setScript.end()){
        this->ParserPy(code,note,empty);
    }else if(setMark.find(map_ext_program.at(ext)) != setMark.end()){
        
    }else if(setFunc.find(map_ext_program.at(ext)) != setFunc.end()){

    }
    this->file.__setlines_code(code);
    this->file.__setlines_note(note);
    this->file.__setlines_empty(empty);
    if(code+note==0){
        this->file.__setrate_note(0);
    }else{
        this->file.__setrate_note((double)(note/(code+note)));
    }
    
}

/*===============================================================================================================*/

void Parser::ParserC(int& code,int& note,int& empty){
    ParserCC(this->file.Getpath(),code,note,empty);
}
void Parser::ParserPy(int& code,int& note,int& empty){
    ParserPyPy(this->file.Getpath(),code,note,empty);
}

/*===============================================================================================================*/

/**
 * @brief 获取所有信息，执行一次即可。
 * 
 */
void Parser::ParseAll(){
    this->Infor();
}