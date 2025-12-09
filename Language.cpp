#include "Language.h"

void Language::addCodes(long code){
    this->lines_code += code;
}

void Language::addNotes(long note){
    this->lines_note += note;
}

void Language::addFiles(){
    this->files++;
}

long Language::getCodes(){
    return this->lines_code;
}

long Language::getNotes(){
    return this->lines_note;
}

long Language::getFiles(){
    return this->files;
}

std::string Language::getName(){
    return this->name_;
}