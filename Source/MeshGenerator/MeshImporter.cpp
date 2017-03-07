// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshGenerator.h"
#include "MeshImporter.h"
#include <sstream>
#include <fstream>

MeshImporter::MeshImporter(const string & filename)
{
	ReadFile(filename);
	CalculateNormals(faces_, vertices_);
}

MeshImporter::~MeshImporter()
{
}

vector<float> MeshImporter::CalculateNormals(vector<uint32_t> faces, vector<float> vertices)
{
	// 1. calculate normals of faces
	vector<float> face_normals(faces.size());
	for (int i = 0; i <= faces.size() - 3; i += 3) {
		int u = faces[i]; // Position of the first value of the first vertex of a triangle
		int v = faces[i + 1]; // Position of the first value of the second vertex of a triangle 

		// Cross product of the first two vertexes of a triangle
		face_normals[i] = (vertices[u + 1] * vertices[v + 2]) - (vertices[u + 2] * vertices[v + 1]);
		face_normals[i + 1] = (vertices[u + 2] * vertices[v]) - (vertices[u] * vertices[v + 2]);
		face_normals[i + 2] = (vertices[u] * vertices[v + 1]) - (vertices[u + 1] * vertices[v]);
	}
	// 2. normalize normals of faces
	// 3. add up normals of vertices from contained faces
	// 3. normalize normals of vertices
	return vector<float>();
}

void MeshImporter::ReadFile(const string & filename)
{
	try
	{
		ifstream ss(filename, ios::binary);
		tinyply::PlyFile file(ss);

		// The count returns the number of instances of the property group. The vectors
		// above will be resized into a multiple of the property group size as
		// they are "flattened"... i.e. verts = {x, y, z, x, y, z, ...}
		file.request_properties_from_element("vertex", { "x", "y", "z" }, vertices_);
		file.request_properties_from_element("vertex", { "nx", "ny", "nz" }, normals_);
		file.request_properties_from_element("vertex", { "red", "green", "blue", "alpha" }, colors_);

		// For properties that are list types, it is possibly to specify the expected count (ideal if a
		// consumer of this library knows the layout of their format a-priori). Otherwise, tinyply
		// defers allocation of memory until the first instance of the property has been found
		// as implemented in file.read(ss)
		file.request_properties_from_element("face", { "vertex_indices" }, faces_, 3);
		file.request_properties_from_element("face", { "texcoord" }, uvCoords_, 6);

		// Now populate the vectors...
		file.read(ss);
	}
	catch (const exception & e)
	{
		cerr << "Caught exception: " << e.what() << endl;
	}
}

vector<float> MeshImporter::GetVertices()
{
	return vertices_;
}

vector<float> MeshImporter::GetNormals()
{
	return normals_;
}

vector<uint8_t> MeshImporter::GetColors()
{
	return colors_;
}

vector<uint32_t> MeshImporter::GetFaces()
{
	return faces_;
}

