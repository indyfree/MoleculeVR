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

	//TODO: NO FILE FOUND
	for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
		Mesh mesh;
		const struct aiMesh* aiMesh = scene->mMeshes[m];

		for (unsigned int i = 0; i < aiMesh->mNumVertices; ++i) {
			// invert x axis to match ue4 coordinate system
			aiVector3D vertex = aiMesh->mVertices[i];
			mesh.vertices.push_back(FVector(vertex.x * (-1), vertex.y, vertex.z));

			aiVector3D normal = aiMesh->mNormals[i];
			mesh.normals.push_back(FVector(normal.x * (-1), normal.y, normal.z));
			
			aiColor4t<float> color = aiMesh->mColors[0][i];
			mesh.colors.push_back(FColor((uint8)(color.r * 255),(uint8)(color.g * 255), (uint8)(color.b * 255), (uint8)(color.a * 255)));
		}

		for (unsigned int i = 0; i < aiMesh->mNumFaces; ++i) {
			aiFace face = aiMesh->mFaces[i];
			for (int j = 0; j < 3; ++j) {
				mesh.faces.push_back(face.mIndices[j]);
			}
		}

		meshes_.push_back(mesh);
	}
}

vector<Mesh>& MeshImporter::GetMeshes()
{
	return meshes_;
}
