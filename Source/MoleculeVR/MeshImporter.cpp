// Fill out your copyright notice in the Description page of Project Settings.

#include "MoleculeVR.h"
#include "MeshImporter.h"

MeshImporter::MeshImporter(const char* path)
{
	ReadFile(path);
}

// Defines import settings: optimize mesh structure
#define molecule_Preset ( \
	aiProcess_RemoveComponent				|  \
	aiProcess_GenSmoothNormals				|  \
	aiProcess_Triangulate					|  \
	aiProcess_JoinIdenticalVertices			|  \
	aiProcess_OptimizeMeshes                |  \
	0 )

bool MeshImporter::ReadFile(const char* filename)
{
	Assimp::Importer importer;

	// We dont want to import Materials, Textures, Animations, etc..
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

	//TODO: User Feedback that file is empty or not readible
	if (scene != NULL) {
		for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
			Mesh mesh;
			const struct aiMesh* aiMesh = scene->mMeshes[m];

			// read vertices, normals and vertex colors and transform to UE4 data types
			for (unsigned int i = 0; i < aiMesh->mNumVertices; ++i) {
				// invert x axis to match UE4 coordinate system
				aiVector3D vertex = aiMesh->mVertices[i];
				mesh.vertices.push_back(FVector(vertex.x * (-1), vertex.y, vertex.z));

				aiVector3D normal = aiMesh->mNormals[i];
				mesh.normals.push_back(FVector(normal.x * (-1), normal.y, normal.z));

				//UE4 saves colors as [0-255] ints
				aiColor4t<float> color = aiMesh->mColors[0][i];
				mesh.colors.push_back(FColor((uint8)(color.r * 255), (uint8)(color.g * 255), (uint8)(color.b * 255), (uint8)(color.a * 255)));
			}

			// read trianges
			for (unsigned int i = 0; i < aiMesh->mNumFaces; ++i) {
				aiFace face = aiMesh->mFaces[i];
				for (unsigned int j = 0; j < 3; ++j) {
					mesh.faces.push_back(face.mIndices[j]);
				}
			}
			meshes_.push_back(mesh);
		}
		return true;
	}

	return false; // No file or mesh found or incompatible file format
}

vector<Mesh>& MeshImporter::GetMeshes()
{
	return meshes_;
}
