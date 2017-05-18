// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshGenerator.h"
#include "MoleculePicker.h"

vector<string> MoleculePicker::FindMeshesInFolder(string base_dir, string extension)
{
	vector<string> mol_paths_relative;
	// return relative path from base dir
	for (string mol_path : SearchRekursiveInFolder(base_dir, extension)) {
		mol_paths_relative.push_back(mol_path.substr(base_dir.size(), mol_path.size() - base_dir.size()));
	}
	return mol_paths_relative;
}

/*
* Shamelessly taken from https://github.com/paulrehkugler/ExtensionSearch/blob/master/search.cpp
*/
vector<string> MoleculePicker::SearchRekursiveInFolder(string directory, string extension) {
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
