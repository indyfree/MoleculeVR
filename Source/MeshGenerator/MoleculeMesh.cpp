// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshGenerator.h"
#include "MoleculeMesh.h"


// Sets default values
AMoleculeMesh::AMoleculeMesh()
{
	Super::CreateMesh("c:/users/tobias/mesh/4cs4.dae");
}

// Called when the game starts or when spawned
void AMoleculeMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMoleculeMesh::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

