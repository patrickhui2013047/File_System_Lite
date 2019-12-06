#include<iostream>
#include"fileSystem.h"

using namespace std;

fileSystem fs;

bool getMenu();
char* buffer2char(char*);
void print( int);

int main() {
	fs.systemLoadDefalut();
	print(-1);
	while (getMenu()) {}
	cout << "Good bye!\n";
	return 0;
}

//TODO:reject GIGO
bool getMenu(){
	while (true) {
		cout << "\n==========\n";
		cout << "n: Create a new file\n"
			<< "d: Delete an existing file\n"
			<< "r: Rename an existing file\n"
			<< "c: Copy an existing file\n"
			<< "m: Move an existing file\n"
			<< "s: Search for an existing file\n"
			<< "N: Create a new folder\n"
			<< "S: Save the system\n"
			<< "q: Quit the system\n";
		char option;
		char* buffer = new char[100];
		 int currentFolder, currentFile;
		cin >> option;
		cout << "\n==========\n";
		switch (option) {
		case 'n'://OK without solving GIGO
			cout << "which folder you would like to create a new file?(Enter the index of the folder)";
			cin >> currentFolder;
			cout << "Enter the the name of the file (20 char allowed):";
			cin >> buffer;
			if (fs.addFile(currentFolder, buffer2char(buffer)) < 0) {}
			else {
				print(currentFolder);
			}
			break;
		case 'd'://OK without solving GIGO
			cout << "which folder hold the file you would like to delete?(Enter the index of the folder)";
			cin >> currentFolder;
			cout << "Which file you would like to delete?(Enter the index of the file)";
			cin >> currentFile;
			if (fs.removeFile(currentFolder, currentFile) < 0) {}
			else {
				print(currentFolder);
			}
			break;
		case 'r'://OK without solving GIGO
			cout << "which folder hold the file you would like to rename?(Enter the index of the folder)";
			cin >> currentFolder;
			cout << "Which file you would like to rename?(Enter the index of the file)";
			cin >> currentFile;
			cout << "Enter the the new name of the file (20 char allowed):";
			cin >> buffer;
			if(fs.renameFile(currentFolder,currentFile,buffer2char(buffer))<0){}
			else {
				print(currentFolder);
			}
			break;
		case 'c':
			cout << "which folder hold the file you would like to copy?(Enter the index of the folder)";
			cin >> currentFolder;
			cout << "Which file you would like to copy?(Enter the index of the file)";
			cin >> currentFile;
			buffer = fs.getFileName(currentFolder,currentFile);
			cout << "which folder you would like to paste?(Enter the index of the folder)";
			cin >> currentFolder;
			if(fs.addFile(currentFolder,buffer)<0){}
			else {
				print(currentFolder);
			}
			break;
		case 'm':
			cout << "which folder hold the file you would like to copy?(Enter the index of the folder)";
				cin >> currentFolder;
				cout << "Which file you would like to copy?(Enter the index of the file)";
				cin >> currentFile;
				buffer = fs.getFileName(currentFolder, currentFile);
				cout << "which folder you would like to paste?(Enter the index of the folder)";
				 int newFolder;
			cin >> newFolder;
			if (fs.addFile(newFolder, buffer) < 0||fs.removeFile(currentFolder,currentFile)<0) {}
			else {
				print(currentFolder);
				print(newFolder);
			}
			break;
		case 's'://OK
			cout << "Enter the the name of the file you would like to search (20 char allowed):";
			cin >> buffer;
			int* j;
			for ( int i = 0; i < fs.getFolderNo(); i++) {
				j = fs.findFileFuzzy(i, 0, buffer2char(buffer));
				if (j[0] == -1)
					continue;
				for (int x = 0; x < fs.getFileNo(i); x++)
					if(j[x]==1)
						cout << "The file " << fs.getFileName(i, j[x]) << " is at Folder" << i << " File" << j[x] << endl;
			}
			break;
		case 'N':
			cout << "Enter the name of the new folder(20 char allowed)";
			cin >> buffer;
			if (fs.addFolder(buffer2char(buffer)) < 0) {}
			else {
				cout << "<===Folder" << fs.getFolderNo() - 1 << ":" << fs.getFolderName(fs.getFolderNo() - 1) << "===>" << endl;
			}
			break;
		case 'S':
			if (fs.systemSave() == 0) {
				cout << "File system saved.\n";
			}
			break;
		case 'q':
			return false;
			break;
		default:
			cout << "Unknown input, please try again\n";
			break;
		}
	}
}

char* buffer2char(char* buffer) {
	int i;
	for (i = 0; i < 20; i++) {
		if (buffer[i] == '\0')
			break;
	}
	char* temp = new char[i];
	for (int j = 0; j <= i; j++) {
		temp[j] = buffer[j];
	}
	return temp;
}

void print( int i) {	
	if (i == -1) {
		for (i = 0; i < fs.getFolderNo(); i++) {
			cout << "<===Folder" << i << ":" << fs.getFolderName(i) << "===>" << endl;
			for ( int j = 0; j < fs.getFileNo(i); j++)
				cout << "   " << j << ":" << fs.getFileName(i, j) << endl;
		}
	}
	else {
		cout << "<===Folder" << i << ":" << fs.getFolderName(i) << "===>" << endl;
		for ( int j = 0; j < fs.getFileNo(i); j++)
			cout << "   " << j << ":" << fs.getFileName(i, j) << endl;

	}

}
