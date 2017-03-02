// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MeshActorBase.h"
#include "StabiloMesh.generated.h"

UCLASS()
class MESHGENERATOR_API AStabiloMesh : public AMeshActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStabiloMesh();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
