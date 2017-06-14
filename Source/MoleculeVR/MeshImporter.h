// Fill out your copyright notice in the Description page of Project Settings.

#include <vector>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

using namespace std;

struct Mesh
{
	vector<FVector> vertices;
	vector<FVector> normals;
	vector<FColor> colors;
	vector<uint32_t> faces;
};

class MOLECULEVR_API MeshImporter
{
public:
	MeshImporter(const char* path);
	~MeshImporter();

	vector<Mesh>& GetMeshes();

private:
	bool ReadFile(const char* path);

	vector<Mesh> meshes_;
};


