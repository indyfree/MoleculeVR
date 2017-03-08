// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshGenerator.h"
#include "SkullMesh.h"


// Sets default values
ASkullMesh::ASkullMesh()
{
	Super::CreateMesh("c:/users/tobias/mesh/skull.ply");

}

// Called when the game starts or when spawned
void ASkullMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkullMesh::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

