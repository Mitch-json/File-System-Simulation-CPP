#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;


class File{
    public:
        string fileName;
        string text;

        File(string name){
            fileName = name;
            text = "";
        }
};

class Directory{
    public:
        string path;
        string dirName;
        vector<Directory*> dirs;
        vector<File*> files;
        Directory* parentDirectory;
        Directory(){
            path = "/";
            parentDirectory = NULL;
        }

        string getPath();
        Directory* mkdir(Directory* pwd, string name);
        Directory* mkdirMany(Directory* pwd, vector<string> newDirs);
        Directory* touch(Directory* pwd , string name);

        Directory* touchMany(Directory* pwd, vector<string> newDirs);
        Directory* nano(Directory* pwd, string name, string content);
        string display(Directory* pwd, string name);
        Directory* cd(Directory* pwd, string dirname);
        Directory* Delete(Directory* pwd, string name);
        Directory* DeleteMany(Directory* pwd, vector<string> dirs);
};

void ls(Directory* pwd);

Directory * runCommand(Directory * pwd, vector<string> args){
    // YOUR CODE GOES HERE
    string command = args[0];
    string text;
    string cName;
    if(args.size() == 2)
        cName = args[1];
    if(args.size() == 3)
        text = args[2];

    if(command == "ls")
        ls(pwd);
    else if(command == "mkdir"){
        if(args.size() == 2)
            pwd = pwd->mkdir(pwd ,args[1]);
        else if(args.size() > 2)
            pwd = pwd->mkdirMany(pwd, args);
        else
            cout<< "mkdir: operand missing!"<<endl;

    }
    else if(command == "touch"){
        if(args.size() == 2)
            pwd = pwd->touch(pwd, args[1]);
        else if(args.size() > 2){
            pwd = pwd->touchMany(pwd, args);
        }
        else
            cout << "touch: operand missing!" <<endl;

    }
    else if(command == "nano"){
        if(args.size() == 3){
            pwd = pwd->nano(pwd, args[1], args[2]);
        }else if(args.size() == 2){
            pwd = pwd->touch(pwd, args[1]);
        }
        else{
            cout<<"nano: operand missing!"<<endl;
        }
    }
    else if(command == "display"){
        if(args.size() == 2){
            pwd->display(pwd, args[1]);
        }else{
            cout<<"Command not found!"<<endl;
        }
    }else if(command == "cd"){
        if(args.size() == 2)
            pwd = pwd->cd(pwd, args[1]);
        else{
            cout<< "cd: operand missing!"<<endl;
        }
    }else if(command == "delete"){
        if(args.size() == 2)
            pwd = pwd->Delete(pwd, args[1]);
        else if(args.size() > 2)
            pwd = pwd->DeleteMany(pwd, args);
        else
            cout <<"delete: operand missing!" <<endl;
    }else if(command == "sort"){
        ls(pwd);
    }else{
        cout<< "No such command!"<<endl;
    }

    return pwd;

}

string Directory::getPath(){
    Directory* current = this;
    string myString = current->path;
    if(myString == "/")
        return "/";
    else{
        string st = myString.substr(0, myString.size()-1);
        return st;
    }
}

void ls(Directory* pwd){
    vector<Directory*> arr = pwd->dirs;
    vector<File*> arr1 = pwd->files;
    if(arr.size() == 0 && arr1.size() ==0){

    }else{
        for(int i=0; i<arr.size(); i++){
            if(arr[i] == NULL){
                continue;
            }else{
                if(i==arr.size()-1)
                {
                    cout<<arr[i]->dirName<<"(d)";
                }
                else
                {
                    cout<<arr[i]->dirName<<"(d) ";
                }
            }
        }
        for(int i=0; i<arr1.size(); i++){
            if(arr1[i] == NULL){
                continue;
            }else{
                if(i==arr1.size()-1)
                {
                    cout<<arr1[i]->fileName;
                }
                else
                {
                    cout<<arr1[i]->fileName<<" ";
                }
            }

        }
        cout<< endl;
    }

}

Directory* Directory::mkdir(Directory* pwd, string name){
    Directory* root = pwd;
    Directory* newDir = new Directory();
    newDir->parentDirectory = pwd;
    newDir->dirName = name;
    newDir->path = root->path + name+"/";
    int i = 0;
    vector<Directory*> directories = pwd->dirs;
    while(i < directories.size()){
        if(directories[i]->dirName == name){
            cout<< "A directory with that name already exists!"<<endl;
            return pwd;
        }
        i++;
    }
    pwd->dirs.push_back(newDir);
    return pwd;
}

Directory* Directory::mkdirMany(Directory* pwd, vector<string> newDirs){
    int i = 1;
    while(i<newDirs.size()){
        pwd = pwd->mkdir(pwd, newDirs[i]);
        i++;
    }
    return pwd;
}

Directory* Directory::touch(Directory* pwd, string name){
    int i=0;
    vector<File*> files = pwd->files;
    while(i < files.size()){
        if(files[i]->fileName == name){
            cout<< "A file with that name already exists!"<<endl;
            return pwd;
        }
        i++;
    }
    File* newFile = new File(name);
    pwd->files.push_back(newFile);

    return pwd;
}


Directory* Directory::nano(Directory* pwd, string name, string content){
    int i=0;
    vector<File*> files = pwd->files;
    while(i < files.size()){
        if(files[i]->fileName == name){
            cout<< "A file with that name already exists!"<<endl;
            return pwd;
        }
        i++;
    }

    File* newFile = new File(name);
    newFile->text = content;
    pwd->files.push_back(newFile);
    return pwd;
}

string Directory::display(Directory* pwd, string name){
    vector<File*> files = pwd->files;
    string content;
    int i=0;
    while(i < files.size()){
        if(files[i]->fileName == name){
            if(files[i]->text != ""){
                content = files[i]->text;
                cout << content<<endl;
                return content;
            }
        }
        i++;
    }
    return "File does not exist";
}

Directory* Directory::cd(Directory* pwd, string dirName){
    vector<Directory*> dirs = pwd->dirs;
    int i=0;
    if(dirName == ".."){
        if(pwd->parentDirectory == NULL)
            return pwd;
        else{
            return pwd->parentDirectory;
        }

    }else if(dirName == "/"){
        while(pwd->parentDirectory != NULL){
            pwd = pwd->parentDirectory;
        }
        return pwd;
    }else{
        while(i < dirs.size()){
            if(dirs[i]->dirName == dirName){
                return dirs[i];
            }
            i++;
        }
        cout<< "No such subdirectory!"<<endl;
    }
}

Directory* Directory::Delete(Directory* pwd, string name){
    vector<Directory*> dirs = pwd->dirs;
    vector<File*> files = pwd->files;

    if(name == "*"){
        pwd->dirs = {};
        pwd->files = {};
        return pwd;
    }else{
        int w=0;
        while(w<files.size()){
            if(files[w]->fileName == name){
                pwd->files[w] = NULL;
                return pwd;
            }
            w++;
        }
        int k=0;
        while(k<dirs.size()){
            if(dirs[k]->dirName == name){
                pwd->dirs[k] = NULL;
                return pwd;
            }
            k++;
        }
        cout<< "No such subdirectory or file!"<<endl;
        return pwd;
    }
}

Directory* Directory::touchMany(Directory* pwd, vector<string> newDirs){
    int i=1;
    while(i< newDirs.size()){
        pwd = pwd->touch(pwd, newDirs[i]);
        i++;
    }
    return pwd;
}

Directory* Directory::DeleteMany(Directory* pwd, vector<string> dirs){
    int i = 1;
    while(i<dirs.size()){
        pwd = pwd->Delete(pwd, dirs[i]);
        i++;
    }
    return pwd;
}
