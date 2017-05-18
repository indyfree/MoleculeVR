// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include "dirent.h" 

using namespace std;

class MESHGENERATOR_API MoleculePicker
{
public:
	static vector<string> FindMeshesInFolder(string base_dir, string extension);

private: 
	static vector<string> SearchRekursiveInFolder(string directory, string extension);
};

