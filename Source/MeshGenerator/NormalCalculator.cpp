// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshGenerator.h"
#include "NormalCalculator.h"

vector<float> NormalCalculator::CalculateVertexNormals(vector<uint32_t> faces, vector<float> vertices)
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

void NormalCalculator::NormalizeVectors(vector<float> &vectors)
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



void NormalCalculator::CalculateNormalsTest()
{
	vector<float> vertices = {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1};

	// Counter Clockwise outside view
	vector<uint32_t> faces = { 0, 2, 1, 0, 1, 3, 0, 3, 2, 1, 2, 3};
	
	//Clockwise outside view
	//vector<uint32_t> faces = { 1, 2, 0, 1, 0, 3, 0, 2, 3, 1, 3, 2};

	vector<float> normals = CalculateVertexNormals(faces, vertices);
}
