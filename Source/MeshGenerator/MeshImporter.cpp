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
	Assimp::Importer importer;
	
	importer.SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS,
		aiComponent_TANGENTS_AND_BITANGENTS |
		aiComponent_MATERIALS |
		aiComponent_BONEWEIGHTS |
		aiComponent_ANIMATIONS |
		aiComponent_LIGHTS |
		aiComponent_CAMERAS
	);

	const aiScene* scene = importer.ReadFile(filename,
		aiProcess_PreTransformVertices |
		aiProcess_JoinIdenticalVertices |
		aiProcess_RemoveComponent |
		aiProcess_OptimizeGraph |
		aiProcess_OptimizeMeshes |
		aiProcess_SortByPType |
		aiProcess_Triangulate);


	const struct aiMesh* mesh = scene->mMeshes[0];

	vertices_ = vector<float>(mesh->mNumVertices);
	for (unsigned int i = 0; i <= mesh->mNumVertices; i+=3) {
		aiVector3D vertex = mesh->mVertices[i];
		vertices_[i] = vertex.x;
		vertices_[i + 1] = vertex.y;
		vertices_[i + 2] = vertex.z;
	}
	
	normals_ = vector<float>(mesh->mNumVertices);
	for (unsigned int i = 0; i <= mesh->mNumVertices; i+=3) {
		aiVector3D normal = mesh->mNormals[i];
		normals_[i] = normal.x;
		normals_[i + 1] = normal.y;
		normals_[i + 2] = normal.z;
	}

	faces_ = vector<uint32_t>(mesh->mNumFaces * 3);
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];
		int face_index = i * 3;
		for (int j = 0; j < 3; ++j) {
			faces_[face_index + j] = face.mIndices[j];
		}
	}
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

