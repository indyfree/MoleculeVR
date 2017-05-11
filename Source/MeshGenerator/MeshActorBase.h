// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RuntimeMeshComponent.h"
#include "MeshImporter.h"
#include "MeshActorBase.generated.h"

UCLASS()
class MESHGENERATOR_API AMeshActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere)
	URuntimeMeshComponent* RuntimeMesh;
	
	// Sets default values for this actor's properties
	AMeshActorBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Main creation method
	virtual void CreateMesh(string path);

	// Set Material to VertexColor to display vertex colors
	void SetVertexColorMaterial(int section);
};
