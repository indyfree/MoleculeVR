// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "CustomActor.generated.h"


UCLASS()
class MESHGENERATOR_API ACustomActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = Materials)
	UProceduralMeshComponent* mesh;
	
public:	
	// Sets default values for this actor's properties
	ACustomActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
