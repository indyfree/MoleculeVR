// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshGenerator.h"
#include "MeshImporter.h"
#include <sstream>
#include <fstream>

MeshImporter::MeshImporter(const string & filename)
{
	ReadFile(filename);
}

MeshImporter::~MeshImporter()
{
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

