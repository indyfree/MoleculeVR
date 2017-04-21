// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshGenerator.h"
#include "MoleculeMesh.h"


// Sets default values
AMoleculeMesh::AMoleculeMesh()
{
	CreateMesh("c:/users/tobias/mesh/4cs4.dae");
}

void AMoleculeMesh::CreateMesh(const char* path)
{
	MeshImporter importer(path);
	vector<Mesh> meshes = importer.GetMeshes();
	Mesh mesh;

	TArray<FRuntimeMeshVertexSimple> vertices;
	TArray<int32> triangles;
	FRuntimeMeshTangent tangent;
	
	int face_index = 0;
	int i = 0;
	
	// Inner Molecule as one section
	while (meshes[i].vertices.size() <= 18) {
		mesh = meshes[i];

		for (int j = 0; j < mesh.vertices.size(); ++j) {
			vertices.Add(FRuntimeMeshVertexSimple(mesh.vertices[j], mesh.normals[j], tangent, mesh.colors[j]));
		}

		for (uint32_t face : mesh.faces) {
			triangles.Add(face += face_index);
		}

		face_index += mesh.vertices.size();
		i++;
	}
	RuntimeMesh->CreateMeshSection(0, vertices, triangles);
	SetVertexColorMaterial(0);

	vertices = TArray<FRuntimeMeshVertexSimple>();
	triangles = TArray<int32>();
	
	// Molecule surfaces as one section
	face_index = 0;
	while (i < meshes.size()) {
		mesh = meshes[i];
		FRuntimeMeshTangent tangent;

		for (int j = 0; j < mesh.vertices.size(); ++j) {
			vertices.Add(FRuntimeMeshVertexSimple(mesh.vertices[j], mesh.normals[j], tangent, mesh.colors[j]));
		}

		for (uint32_t face : mesh.faces) {
			triangles.Add(face += face_index);
		}

		face_index += mesh.vertices.size();
		i++;
	}
	RuntimeMesh->CreateMeshSection(1, vertices, triangles);
	SetVertexColorMaterial(1);
}

// Called when the game starts or when spawned
void AMoleculeMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMoleculeMesh::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

