// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshGenerator.h"
#include "MeshImporter.h"
#include <sstream>
#include <fstream>

MeshImporter::MeshImporter()
{
	ReadFile("C:/Users/Tobias/mesh/Stabilo.ply");

}

MeshImporter::~MeshImporter()
{
}

tinyply::PlyFile MeshImporter::ReadFile(const std::string & filename)
{
	try
	{
		std::ifstream ss(filename, std::ios::binary);
		tinyply::PlyFile file(ss);
		return file;
	}
	catch (const std::exception & e)
	{
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	return tinyply::PlyFile();
}
