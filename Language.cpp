#include "Language.h"
#include <vector>

void Language::addCodes(long code){
    this->lines_code += code;
}

void Language::addNotes(long note){
    this->lines_note += note;
}

void Language::addEmpty(long empty){
    this->lines_empty += empty;
}

void Language::addFile(){
    this->files++;
}

void Language::setExtensionSet(const std::vector<std::string> exs){
    for(const auto item:exs){
        this->ExtensionSet.insert(item);
    }
}
void Language::setExtensionSet(const std::string ext){
    this->ExtensionSet.insert(ext);
}

long Language::getCodes() const{
    return this->lines_code;
}

long Language::getNotes() const{
    return this->lines_note;
}

long Language::getEmpty() const{
    return this->lines_empty;
}

long Language::getFiles() const{
    return this->files;
}

std::string Language::getName() const{
    return this->name_;
}

bool Language::IsBelongTo(std::string& extension){
    return this->ExtensionSet.find(extension) != this->ExtensionSet.end();
}