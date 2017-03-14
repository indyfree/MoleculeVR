// Fill out your copyright notice in the Description page of Project Settings.

#include <vector>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

using namespace std;

class MESHGENERATOR_API MeshImporter
{
public:
	MeshImporter(const char* path);
	~MeshImporter();

	vector<FVector>& GetVertices();
	vector<FVector>& GetNormals();
	vector<FColor>& GetColors();
	vector<uint32_t>& GetFaces();

private:
	void ReadFile(const char* path);

	vector<FVector> vertices_;
	vector<FVector> normals_;
	vector<FColor> colors_;
	vector<uint32_t> faces_;
};
