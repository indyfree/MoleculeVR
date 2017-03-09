// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshGenerator.h"
#include "MeshImporter.h"

MeshImporter::MeshImporter(const char* path)
{
	ReadFile(path);
}

MeshImporter::~MeshImporter()
{
}

void MeshImporter::ReadFile(const char* filename)
{
	scene = aiImportFile(filename, aiProcessPreset_TargetRealtime_Fast);
	const struct aiMesh* mesh = scene->mMeshes[0];

}

vector<float>& MeshImporter::GetVertices()
{
	return vertices_;
}

vector<float>& MeshImporter::GetNormals()
{
	return normals_;
}

vector<uint8_t>& MeshImporter::GetColors()
{
	return colors_;
}

vector<uint32_t>& MeshImporter::GetFaces()
{
	return faces_;
}

