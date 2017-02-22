// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshGenerator.h"
#include "MeshImporter.h"
#include <sstream>
#include <fstream>

MeshImporter::MeshImporter(const std::string & filename)
{
	ReadFile(filename);

}

MeshImporter::~MeshImporter()
{
}

std::vector<float> MeshImporter::GetVertices()
{
	return vertices;
}

std::vector<uint8_t> MeshImporter::GetColors()
{
	return colors;
}

std::vector<uint32_t> MeshImporter::getFaces()
{
	return faces;
}

tinyply::PlyFile MeshImporter::ReadFile(const std::string & filename)
{
	try
	{
		std::ifstream ss(filename, std::ios::binary);
		tinyply::PlyFile file(ss);

		// Define containers to hold the extracted data. The type must match
		// the property type given in the header. Tinyply will interally allocate the
		// the appropriate amount of memory.

		uint32_t vertexCount, normalCount, colorCount, faceCount, faceTexcoordCount, faceColorCount;
		vertexCount = normalCount = colorCount = faceCount = faceTexcoordCount = faceColorCount = 0;

		// The count returns the number of instances of the property group. The vectors
		// above will be resized into a multiple of the property group size as
		// they are "flattened"... i.e. verts = {x, y, z, x, y, z, ...}
		vertexCount = file.request_properties_from_element("vertex", { "x", "y", "z" }, vertices);
		normalCount = file.request_properties_from_element("vertex", { "nx", "ny", "nz" }, normals);
		colorCount = file.request_properties_from_element("vertex", { "red", "green", "blue", "alpha" }, colors);

		// For properties that are list types, it is possibly to specify the expected count (ideal if a
		// consumer of this library knows the layout of their format a-priori). Otherwise, tinyply
		// defers allocation of memory until the first instance of the property has been found
		// as implemented in file.read(ss)
		faceCount = file.request_properties_from_element("face", { "vertex_indices" }, faces, 3);
		faceTexcoordCount = file.request_properties_from_element("face", { "texcoord" }, uvCoords, 6);

		// Now populate the vectors...
		file.read(ss);

		// Good place to put a breakpoint!
		return file;
	}
	catch (const std::exception & e)
	{
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	return tinyply::PlyFile();
}
