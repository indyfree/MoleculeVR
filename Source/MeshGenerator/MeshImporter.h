// Fill out your copyright notice in the Description page of Project Settings.

#include "tinyply.h"

class MESHGENERATOR_API MeshImporter
{
public:
	MeshImporter(const std::string & filename);
	~MeshImporter();

	std::vector<float> GetVertices();
	std::vector<uint8_t> GetColors();
	std::vector<uint32_t> getFaces();

private:
	tinyply::PlyFile ReadFile(const std::string &filename);

	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<uint8_t> colors;

	std::vector<uint32_t> faces;
	std::vector<float> uvCoords;
};
