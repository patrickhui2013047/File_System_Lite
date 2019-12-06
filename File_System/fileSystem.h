#pragma once
#include<iostream>

/*
 int is the index of array, use for identifying
char* is mostly a string unless specified, use for folder name, file name or file contents
short is for the status of execution. If the value if negative, there is an error occured
returning -1000 mean unknown error occured.
*/

class fileSystem
{
public:
	fileSystem();

	/*
	char* getFolderName( int i)
	input:
		i: index of folder
	return:
		name of folder
	*/
	char* getFolderName( int);

	/*
	 int getFolderNo()
	return:
		number of folders
	*/
	 int getFolderNo();

	/*
	char* getFileName( int i, int j)
	input:
		i: index of folder
		j: index of file
	return:
		file name
	*/
	char* getFileName( int, int);

	/*
	char* getFile( int i,  int j)
	input:
		i: index of folder
		j: index of file
	return:
		file content
	*/
	char* getFile( int,  int);

	/*
	 int getFileNo( int i)
	input:
		i: index of folder
	return:
		number of files in the folder
	*/
	 int getFileNo( int);

	/*
	short addFolder(char* name)
	input:
		name: folder name to add
	return:
		status of execution
		-1 when existing folder
		otherwise return the index of new folder
	*/
	short addFolder(char*);

	/*
	short addFile( int i, char* name)
	input:
		i: index of folder
		name: file name to add
	return:
		status of execution
		-1 when existing file
		otherwise return the index of new file
	*/
	short addFile( int, char*);

	/*
	short removeFolder( int)
	input:
		i: index of folder
	return:
		status of execution
		-1 when no existing folder
		0 when success
	*/
	short removeFolder( int);

	/*
	short removeFile( int i,  int j)
	input:
		i: index of folder

	return:
		status of execution
		-1 when no existing file
		0 when success
	*/
	short removeFile( int,  int);

	/*
	short renameFile( int i,  int j, char* name)
	input:
		i: index of folder
		j: index of file
		name: new name of the file
	return:
		status of execution
		-1 when no existing file
		0 when success
	*/
	short renameFile( int,  int, char*);

	/*
	short renameFolder( int i, char* name)
	input:
		i: index of folder
		name: new name of the folder
	return:
		status of execution
		-1 when no existing folder
		0 when success
	*/
	short renameFolder( int, char*);

	/*
	int findFile( int i, char* name)
	input:
		i: index of folder
		name: name of the file
	return:
		status of execution
		-1 when no existing file
		return the index of the file
	*/
	int findFile( int, char*);

	/*
	int findFileFuzzy( int i,  int j,char* name)
	input:
		i: index of folder
		j: index of folder to start search
		name: name of the file
	return:
		status of execution
		return an array same length with the file number in folder, show is the name match the keyword
		0 mean not match, 1 mean match
	*/
	int* findFileFuzzy( int,  int, char*);

	/*
	int findFolder(char* name)
	input:
		name: name of the folder
	return:
		status of execution
		-1 when no existing folder
		return the index of the folder
	*/
	int findFolder(char*);

	/*
	short systemSave(std::string path)
	save the system into a file
	input:
		path: the path to save the file system. Default value is C:/Users/Public/Documents
	return:
		0 when success
		neagtive value when error occured
	*/
	short systemSave(std::string = "C:/Users/Public/Documents/");

	/*
	short systemLoad(std::string path)
	load the system form a file
	input:
		path: the path to load the file system. Default value is C:/Users/Public/Documents
	return:
		0 when success
		neagtive value when error occured
	*/
	short systemLoad(std::string = "C:/Users/Public/Documents/");

	/*
	short systemLoadDefault()
	load the system for debug
	return:
		0 when success
		neagtive value when error occured
	*/
	short systemLoadDefalut();

private:
	char*** _system;/*
				   1st layer for folder index
				   2nd layer for file index
				   3rd layer for file name
				   */
	char** _FoldersName;	//storage the name of folders
	 int _FolderNumber;		//number of folders
	 int* _FileNumber;		//number of files
	std::string _Defaultpath;
};

