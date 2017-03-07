// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshGenerator.h"
#include "MeshImporter.h"
#include <sstream>
#include <fstream>

MeshImporter::MeshImporter(const string & filename)
{
	ReadFile(filename);
	normals_ = CalculateVertexNormals(GetFaces(), GetVertices());
	CalculateNormalsTest();
}

MeshImporter::~MeshImporter()
{
}

vector<float> MeshImporter::CalculateVertexNormals(vector<uint32_t> faces, vector<float> vertices)
{
	// 1. calculate faces normals
	vector<float> face_normals(faces.size());
	vector<float> u(3);
	vector<float> v(3);

	for (int i = 0; i <= faces.size() - 3; i += 3) {
		int p1 = faces[i] * 3; // Position of the first value of the first vertex of a triangle
		int p2 = faces[i + 1] * 3; // Position of the first value of the second vertex of a triangle 
		int p3 = faces[i + 2] * 3; // Position of the first value of the third vertex of a triangle 

		//calculate u and v vectors
		for (int j = 0; j < u.size(); ++j) {
			u[j] = vertices[p2 + j] - vertices[p1 + j];
			v[j] = vertices[p3 + j] - vertices[p1 + j];
		}

		// Cross product of two sides of the triangle
		face_normals[i]		= (u[1] * v[2]) - (u[2] * v[1]);
		face_normals[i + 1] = (u[2] * v[0]) - (u[0] * v[2]);
		face_normals[i + 2] = (u[0] * v[1]) - (u[1] * v[0]);
	}


	// 2. normalize faces normals
	NormalizeVectors(face_normals);
	
	// 3. add up normals of vertices from contained faces
	vector<float> vertex_normals(vertices.size());

	for (int i = 0; i < faces.size(); ++i) {

		uint32_t vertex_index = faces[i] * 3;
		uint32_t face_normal_index = (i / 3) * 3;
		
		for (int k = 0; k < 3; ++k) {
			vertex_normals[vertex_index + k] += face_normals[face_normal_index + k];
		}
	}

	// 3. normalize vertex vertices
	NormalizeVectors(vertex_normals);
	return vertex_normals;
}

void MeshImporter::NormalizeVectors(vector<float> &vectors)
{
	if (vectors.size() % 3 == 0) {
		for (int i = 0; i <= vectors.size() - 3; i += 3) {
			float magnitude = sqrt(pow(vectors[i], 2) + pow(vectors[i + 1], 2) + pow(vectors[i + 2], 2));

			vectors[i] = vectors[i] / magnitude;
			vectors[i + 1] = vectors[i + 1] / magnitude;
			vectors[i + 2] = vectors[i + 2] / magnitude;
		}
	}
}



void MeshImporter::CalculateNormalsTest()
{
	vector<float> vertices = {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1};
	// Counter Clockwise outside view
	vector<uint32_t> faces = { 0, 2, 1, 0, 1, 3, 0, 3, 2, 1, 2, 3};
	
	//Clockwise outside view
	//vector<uint32_t> faces = { 1, 2, 0, 1, 0, 3, 0, 2, 3, 1, 3, 2};

	vector<float> normals = CalculateVertexNormals(faces, vertices);
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

