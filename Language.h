#pragma once
#include <string>
class Language{
private:
    std::string name_;
    long lines_code;
    long lines_note;
    int files;
public:
    Language(const std::string& name):name_(name),lines_code(0),lines_note(0),files(0){}


public:
    
    void addCodes(long code);
    void addNotes(long note);
    void addFiles();

    long getCodes();
    long getNotes();
    long getFiles();
    std::string getName();
};