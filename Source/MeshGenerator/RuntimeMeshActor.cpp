// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshGenerator.h"
#include "RuntimeMeshActor.h"


// Sets default values
ARuntimeMeshActor::ARuntimeMeshActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARuntimeMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARuntimeMeshActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

