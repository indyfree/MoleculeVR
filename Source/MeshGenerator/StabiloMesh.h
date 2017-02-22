// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RuntimeMeshComponent.h"
#include "StabiloMesh.generated.h"

UCLASS()
class MESHGENERATOR_API AStabiloMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere)
	URuntimeMeshComponent* RuntimeMesh;

	// Sets default values for this actor's properties
	AStabiloMesh();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
