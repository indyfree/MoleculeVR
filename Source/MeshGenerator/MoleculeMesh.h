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

	// Set physic simulation
	UFUNCTION(BlueprintCallable)
	void SetSimulatePhysics(bool simulate);

	// Toggles the visibility of the molecule surface
	UFUNCTION(BlueprintCallable)
	void ToggleSurface();

	// Scale the Molecule by given steps
	UFUNCTION(BlueprintCallable)
	void ScaleMolecule(float step);

	// Main creation method
	UFUNCTION(BlueprintCallable)
	void CreateMesh(FString path);

	// Called when Actor is constructed
	void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


private:
	TArray<FRuntimeMeshVertexSimple> ExtractSectionVertices(vector<Mesh> meshes);
	TArray<int32> ExtractSectionFaces(vector<Mesh> meshes);

	void SetCollisionConvexMesh(vector<Mesh> collision_meshes);
};
