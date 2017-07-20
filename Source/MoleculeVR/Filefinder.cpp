// Fill out your copyright notice in the Description page of Project Settings.

#include "MoleculeVR.h"
#include "FileFinder.h"

vector<string> FileFinder::FindFilesInFolder(string base_dir, string extension)
{
	vector<string> relative_paths;
	// return relative path from base dir
	for (string full_path : SearchRekursiveInFolder(base_dir, extension)) {
		relative_paths.push_back(full_path.substr(base_dir.size(), full_path.size() - base_dir.size()));
	}
	return relative_paths;
}

/*
* Shamelessly taken from https://github.com/paulrehkugler/ExtensionSearch/blob/master/search.cpp
* All Credits to the Author
*/
vector<string> FileFinder::SearchRekursiveInFolder(string directory, string extension) {
	vector<string> results;

	DIR* dir_point = opendir(directory.c_str());
	dirent* entry = readdir(dir_point);

	while (entry) {									// if !entry then end of directory
		string fname = entry->d_name;
		if (entry->d_type == DT_DIR) {				// if entry is a directory
			if (fname != "." && fname != "..") {
				vector<string> sub_dir_files = SearchRekursiveInFolder(directory +  entry->d_name + "/", extension);
				results.insert(results.end(), sub_dir_files.begin(), sub_dir_files.end());	// search through it
			}
		}
		else if (entry->d_type == DT_REG) {		// if entry is a regular file
			if (fname.find(extension, (fname.length() - extension.length())) != string::npos)
				results.push_back(directory + fname);		// add filename to results vector
		}
		entry = readdir(dir_point);
	}
	return results;
}
