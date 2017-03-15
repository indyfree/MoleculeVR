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

#define molecule_Preset ( \
	aiProcess_RemoveComponent				|  \
	aiProcess_GenSmoothNormals				|  \
	aiProcess_Triangulate					|  \
	aiProcess_JoinIdenticalVertices			|  \
	aiProcess_OptimizeMeshes                |  \
	0 )

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


	const aiScene* scene = importer.ReadFile(filename, molecule_Preset);
	int face_index = 0;

	//Surface Mesh has Vertices > 18, all mols have ALWAYS 18 vertices at other meshes?
	for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
		const struct aiMesh* mesh = scene->mMeshes[m];

		for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
			aiVector3D vertex = mesh->mVertices[i];
			vertices_.push_back(FVector(vertex.x * (-1), vertex.y, vertex.z));

			aiVector3D normal = mesh->mNormals[i];
			normals_.push_back(FVector(normal.x * (-1), normal.y, normal.z));
			
			aiColor4t<float> color = mesh->mColors[0][i];
			colors_.push_back(FColor((uint8)(color.r * 255),(uint8)(color.g * 255),(uint8)(color.b * 255), (uint8)(color.a * 255)));

		}

		for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
			aiFace face = mesh->mFaces[i];
			for (int j = 0; j < 3; ++j) {
				faces_.push_back(face.mIndices[j] + face_index);
			}
		}

		face_index += mesh->mNumVertices;
	}
}

vector<FVector>& MeshImporter::GetVertices()
{
	return vertices_;
}

vector<FVector>& MeshImporter::GetNormals()
{
	return normals_;
}

vector<FColor>& MeshImporter::GetColors()
{
	return colors_;
}

vector<uint32_t>& MeshImporter::GetFaces()
{
	return faces_;
}

