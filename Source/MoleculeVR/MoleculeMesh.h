// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RuntimeMeshComponent.h"
#include "MeshImporter.h"
#include "MoleculeMesh.generated.h"

UCLASS()
class MOLECULEVR_API AMoleculeMesh : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AMoleculeMesh();

	UPROPERTY(EditAnywhere)
	URuntimeMeshComponent* RuntimeMesh;
	UMaterial* VertexColorMaterial;
	
	// Main creation method
	UFUNCTION(BlueprintCallable)
	void CreateMesh(FString path);
	
	// Set physic simulation
	UFUNCTION(BlueprintCallable)
	void SetSimulatePhysics(bool simulate);

	// Toggles the visibility of the molecule surface
	UFUNCTION(BlueprintCallable)
	void ToggleSurface();

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
	
	// Get Material to VertexColor to display vertex colors
	void GetVertexColorMaterial();

};
