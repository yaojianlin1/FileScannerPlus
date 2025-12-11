#pragma once
#include <string>
#include <unordered_set>
#include <vector>
class Language{
private:
    std::string name_;
    long lines_code;
    long lines_note;
    long lines_empty;
    int files;
    
    std::unordered_set<std::string> ExtensionSet;
public:
    Language() = default;
    Language(const std::string& name):name_(name),lines_code(0),lines_note(0),lines_empty(0),files(0),ExtensionSet({}){}
    Language(const Language& other):name_(other.name_),lines_code(other.lines_code),lines_note(other.lines_note),lines_empty(other.lines_empty),files(other.files),ExtensionSet(other.ExtensionSet){}
    Language& operator=(const Language& other){
        if(this != &other){
            this->name_ = other.name_;
            this->lines_code = other.lines_code;
            this->lines_note = other.lines_note;
            this->lines_empty = other.lines_empty;
            this->files = other.files;
            this->ExtensionSet = other.ExtensionSet;
        }
        return *this;
    }
    ~Language() = default;

public:
    
    void addCodes(long code);
    void addNotes(long note);
    void addEmpty(long empty);
    void addFile();
    void setExtensionSet(const std::vector<std::string> exs);
    void setExtensionSet(const std::string ext);

    long getCodes() const;
    long getNotes() const;
    long getFiles() const;
    long getEmpty() const;
    std::string getName() const;

    bool IsBelongTo(std::string& extension);
};