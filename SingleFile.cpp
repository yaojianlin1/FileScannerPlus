#include "SingleFile.h"

/*======================================================================================================*/
/*======    set    =====*/

void FileInformation::__setpath(std::string path){
    this->path = fs::path(path);
}
void FileInformation::__setis_program(bool x){
    this->is_program = x;
}
void FileInformation::__setname_program(std::string name){
    this->name_program = name;
}
void FileInformation::__setlines_code(int code){
    this->lines_code = code;
}
void FileInformation::__setlines_note(int note){
    this->lines_note = note;
}
void FileInformation::__setlines_empty(int empty){
    this->lines_empty = empty;
}
void FileInformation::__setrate_note(double rate){
    this->rate_note = rate;
}

/*======================================================================================================*/
/*=====    get    =====*/

fs::path FileInformation::Getpath(){
    return this->path;
}
bool FileInformation::Getis_program(){
    return this->is_program;
}
std::string FileInformation::Getname_program(){
    return this->name_program;
}
int FileInformation::Getlines_code(){
    return this->lines_code;
}
int FileInformation::Getlines_note(){
    return this->lines_note;
}
int FileInformation::Getlines_empty(){
    return this->lines_empty;
}
double FileInformation::Getrate_note(){
    return this->rate_note;
}

/*====================================================================================================*/