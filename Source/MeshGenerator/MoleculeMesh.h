// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MeshActorBase.h"
#include "MoleculeMesh.generated.h"

UCLASS()
class MESHGENERATOR_API AMoleculeMesh : public AMeshActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoleculeMesh();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Main creation method
	virtual void CreateMesh(const char* path) override;

private:
	TArray<FRuntimeMeshVertexSimple> ExtractSectionVertices(vector<Mesh> meshes);
	TArray<int32> ExtractSectionFaces(vector<Mesh> meshes);

	void ToggleSurface();
};
