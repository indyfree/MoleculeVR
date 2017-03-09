// Fill out your copyright notice in the Description page of Project Settings.

#include <vector>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

class MESHGENERATOR_API MeshImporter
{
public:
	MeshImporter(const char* path);
	~MeshImporter();

	vector<float>& GetVertices();
	vector<float>& GetNormals();
	vector<uint8_t>& GetColors();
	vector<uint32_t>& GetFaces();

private:
	void ReadFile(const char* path);

	vector<float> vertices_;
	vector<float> normals_;
	vector<uint8_t> colors_;
	vector<uint32_t> faces_;
	vector<float> uvCoords_;

	const struct aiScene* scene = NULL;
};
