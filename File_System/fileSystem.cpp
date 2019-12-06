#include "fileSystem.h"
#include<iostream>
#include<fstream>
using namespace std;



//OK
bool equal(char* str1,char* str2){
	if (sizeof(str1) == sizeof(str2)) {
		for (int x = 0; x < sizeof(str1); x++) {
			if (str1[x] == str2[x]) {}
			else { return false; }
		}
	}
	else { return false; }
	return true;
}

bool equalFuzzy(char* str1, char* str2) {
	if (sizeof(str1) == sizeof(str2)) {
		for (int x = 0; x < sizeof(str1); x++) {
			if (str1[x] == '\0' || str2[x] == '\0')
				return true;
			if (str1[x] == str2[x]) {}
			else { return false; }
		}
	}
	else { return false; }
	return true;
}

//OK
fileSystem::fileSystem()
{
	_Defaultpath = "C:/Users/Public/Documents";
	_FolderNumber = 1;
	_FileNumber = new  int [_FolderNumber];      //Creating a 1 dimentional array -->> store file number -->> to record the number of files in the folder
	_FileNumber[0] = 1;                         //set first folder contains one file
	_system = new char** [_FolderNumber];       //a 3d array contains each folder-->> distinguish each file-->> store file name
	for (int i = 0; i < _FolderNumber; i++) {
		_system[i] = new char*[_FileNumber[i]];
		for (int j = 0; j < _FileNumber[i]; j++)
			_system[i][j] = new char[100];
	}
	_FoldersName = new char*[_FolderNumber];
	for (int i = 0; i < _FolderNumber; i++)
		_FoldersName[i] = new char[100];
}


//TODO:test the function
//TODO:DEBUG

// i->Folder index, j->File Index

//OK
char* fileSystem::getFolderName( int i) {
	if (i >= _FolderNumber)
		return nullptr;
	return _FoldersName[i];
}

//OK
 int fileSystem::getFolderNo() {
	return _FolderNumber;
}

//OK
char* fileSystem::getFileName( int i,  int j) {
	if (i >= _FolderNumber || j >= _FileNumber[i] || _system[i] == nullptr)
		return nullptr;
	return _system[i][j];
}


//not tested
char* fileSystem::getFile( int i,  int j){
	if (i >= _FolderNumber || j >= _FileNumber[i] || _system[i] == nullptr)
		return nullptr;
	//solve later
	return new char[1000];
}


//OK
 int fileSystem::getFileNo( int i) {
	return _FileNumber[i];
}


//logic OK not refused GIGO
short fileSystem::addFolder(char* name) {
	
		int stat = findFolder(name);
		if (stat != -1) {
			cout << "There is already a folder named as " << name;
			return -1;
		}
			
		if (stat == -2) {
			return -2;
		}
			
		char*** temp = new char**[(int)_FolderNumber + 1];
		for (int x = 0; x < _FolderNumber; x++)
			temp[x] = _system[x];
		temp[_FolderNumber] = nullptr;
		_system = temp;
		_FileNumber[_FolderNumber] = 0;
		char** temp2 = new char*[(int)_FolderNumber + 1];
		for (int x = 0; x < _FolderNumber; x++)
			temp2[x] = _FoldersName[x];
		_FoldersName[_FolderNumber] = name;
		_FolderNumber++;
		return _FolderNumber - 1;
	
	
	
}

//OK
short fileSystem::addFile( int i, char* name){
	
		if (_system[i] == nullptr) {
			_system[i] = new char* [1];
			_system[i][0] = name;
			_FileNumber[i] = 1;
			return 0;
		}

		if (findFile(i,name) != -1){
			cout << "There is already a file named as " << name;
			return - 1;
		}
		char** temp = new char*[(int)_FileNumber[i] + 1];
		for (int x = 0; x < _FileNumber[i]; ++x)
			temp[x] = _system[i][x];
		temp[_FileNumber[i]] = name;
		_system[i] = temp;
		_FileNumber[i]++;
		return 0;
	
	
}


/*
short fileSystem::removeFolder( int i){

		if (i >= _FolderNumber) {
			cout << "There are no such folder";
			return -1;
		}
		
		char*** temp = new char**[_FolderNumber - 1];
		_FolderNumber--;
		for (int x = 0; x < _FolderNumber; ++x) {
			if (x >= i)
				temp[x] = _system[x + 1];
			else
				temp[x] = _system[x];
		}	
		_system = temp;		
		return 0;
	
	
}
*/

//OK
short fileSystem::removeFile( int i,  int j){
	
		if (j >= _FileNumber[i] || i >= _FolderNumber) {
			cout << "There are no such file";
			return -1;
		}
		char** temp = new char*[_FileNumber[i] - 1];
		_FileNumber[i]--;
		for (int x = 0; x < _FileNumber[i]; ++x)
			if(x>=j)
				temp[x] = _system[i][x+1];
			else
				temp[x] = _system[i][x];
		_system[i] = temp;
		
		return 0;
	
	
}


//OK
short fileSystem::renameFile( int i,  int j, char* name){
	
		int stat = findFile(i, name);
		if (stat != -1) {
			cout << "There is already a file named as " << name << endl;
			return -1;
		}
		_system[i][j] = name;
		return 0;
	

}


//not tested
short fileSystem::renameFolder( int i, char* name) {
	
		if (findFolder(name) == -1) {
			cout << "There is already a folder named as " << name;
			return -1;
		}

		_FoldersName[i] = name;
		return 0;

}


//OK
int fileSystem::findFile( int i, char* name){
	
		if (i >= _FolderNumber) {
			cout << "No such folder";
			return -2;
		}

		if (_FileNumber[i] == 0)
			return -1;
		for (int x = 0; x < _FileNumber[i]; x++){
			if (equal(_system[i][x], name))
				return x;
		}
		return -1;
	

	
}

//OK
int* fileSystem::findFileFuzzy( int i,  int j,char* name) {
		int* temp = new int[_FileNumber[i]];
		for (int x = 0; x < _FileNumber[i]; x++) {
			if (equalFuzzy(name, _system[i][x])) 
				temp[x] = 1;
			else
				temp[x] = 0;
			
		}
		return temp;
}

//not tested
int fileSystem::findFolder(char* name) {
	
		for (int x = 0; x < _FolderNumber; x++)
			if (equal(_FoldersName[x],name))
				return x;
		return - 1;
	
}

//OK
short fileSystem::systemSave(std::string path) {
	
		std::string filepath = path + "folderName";
		std::fstream fs;
		fs.open(filepath, std::ios::out);
		
		for ( int i = 0; i < _FolderNumber; i++) {
			fs << _FoldersName[i];
			if (i == _FolderNumber - 1)
				continue;
			fs << "\n";
		}
		
		fs.close();
		for ( int i = 0; i < _FolderNumber; i++) {
			filepath = path + _FoldersName[i];
			fs.open(filepath, std::ios::out);
			
			for ( int j = 0; j < _FileNumber[i]; j++) {
				fs << _system[i][j];
				if (j == _FileNumber[i] - 1)
					continue;
				fs << "\n";
			}
			
			fs.close();
		}
		

		return 0;
	
	
}

//problem with returning the string into a data structure
//TODO:Debug
short fileSystem::systemLoad(std::string path) {
	std::fstream fs;
	std::string filepath = path + "folderName";
	fs.open(filepath, std::ios::in);
	char buffer[1000];
	fs >> buffer;
	
	return 0;
}

//OK
short fileSystem::systemLoadDefalut() {
	_FolderNumber = 2;
	_FileNumber = new  int[_FolderNumber];
	_FileNumber[0] = 6;
	_FileNumber[1] = 5;
	_system = new char** [_FolderNumber];
	for (int i = 0; i < _FolderNumber; i++) {
		_system[i] = new char* [_FileNumber[i]];
	}
	_system[0][0] = (char*)"EIE1000.txt";
	_system[0][1] = (char*)"EIE2000.txt";
	_system[0][2] = (char*)"EIE3000.txt";
	_system[0][3] = (char*)"EIE4000.txt";
	_system[0][4] = (char*)"IEexplorer";
	_system[0][5] = (char*)"Chrome";

	_system[1][0] = (char*)"COMP1000.txt";
	_system[1][1] = (char*)"COMP2000.txt";
	_system[1][2] = (char*)"COMP3000.txt";
	_system[1][3] = (char*)"COMP4000.txt";
	_system[1][4] = (char*)"SAFARI";

	_FoldersName = new char* [_FolderNumber];
	_FoldersName[0] = (char*)"WINDOWS";
	_FoldersName[1] = (char*)"IOS";
	return 0;
}
