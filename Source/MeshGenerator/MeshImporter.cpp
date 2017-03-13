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
		aiComponent_CAMERAS |
		aiComponent_TEXTURES |
		aiComponent_TEXCOORDS
	);

#define max_Quality_Preset ( \
	aiProcess_CalcTangentSpace				|  \
	aiProcess_GenSmoothNormals				|  \
	aiProcess_JoinIdenticalVertices			|  \
	aiProcess_ImproveCacheLocality			|  \
	aiProcess_LimitBoneWeights				|  \
	aiProcess_RemoveRedundantMaterials      |  \
	aiProcess_SplitLargeMeshes				|  \
	aiProcess_Triangulate					|  \
	aiProcess_GenUVCoords                   |  \
	aiProcess_SortByPType                   |  \
	aiProcess_FindDegenerates               |  \
	aiProcess_FindInvalidData               |  \
	aiProcess_FindInstances                 |  \
	aiProcess_ValidateDataStructure         |  \
	aiProcess_OptimizeMeshes                |  \
	aiProcess_OptimizeGraph					|  \
	0 )

#define molecule_Preset ( \
	aiProcess_RemoveComponent				|  \
	aiProcess_SplitLargeMeshes				|  \
	aiProcess_GenSmoothNormals				|  \
	aiProcess_Triangulate					|  \
	aiProcess_JoinIdenticalVertices			|  \
	aiProcess_OptimizeMeshes                |  \
	aiProcess_OptimizeGraph					|  \
	aiProcess_PreTransformVertices			|  \
	0 )

	// TODO revert last two presets to gather color
	const aiScene* scene = importer.ReadFile(filename, molecule_Preset);


	for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
		const struct aiMesh* mesh = scene->mMeshes[m];

		for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
			aiVector3D vertex = mesh->mVertices[i];
			vertices_.push_back(vertex.x);
			vertices_.push_back(vertex.y);
			vertices_.push_back(vertex.z);
		}

		for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
			aiVector3D normal = mesh->mNormals[i];
			normals_.push_back(normal.x);
			normals_.push_back(normal.y);
			normals_.push_back(normal.z);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
			aiFace face = mesh->mFaces[i];
			for (int j = 0; j < 3; ++j) {
				faces_.push_back(face.mIndices[j]);
			}
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

