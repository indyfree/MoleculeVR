// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MeshActorBase.h"
#include "BuddhaMesh.generated.h"

UCLASS()
class MESHGENERATOR_API ABuddhaMesh : public AMeshActorBase 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuddhaMesh();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
