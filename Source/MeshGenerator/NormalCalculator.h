// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <vector>

using namespace std;

/**
 * 
 */
class MESHGENERATOR_API NormalCalculator
{
public:
	static vector<float> CalculateVertexNormals(vector<uint32_t> faces, vector<float> vertices);
private:
	static void NormalizeVectors(vector<float> &vectors);
	static void CalculateNormalsTest();
};
