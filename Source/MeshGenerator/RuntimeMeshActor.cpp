// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshGenerator.h"
#include "RuntimeMeshActor.h"


// Sets default values
ARuntimeMeshActor::ARuntimeMeshActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RuntimeMesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("Runtime Mesh"));
	RootComponent = RuntimeMesh;

	TArray<FRuntimeMeshVertexSimple> Packed_Vertices;
	TArray<FVector> Vertices;
	TArray<FVector> Normals;
	TArray<FColor> VertexColors;
	TArray<int32> Triangles;

	Vertices.Add(FVector(0, 0, 0));
	VertexColors.Add(FColor::White);
	
	Vertices.Add(FVector(100, 0, 0));
	VertexColors.Add(FColor::White);

	Vertices.Add(FVector(0, 100, 0));
	VertexColors.Add(FColor::White);
	
	Vertices.Add(FVector(0, 0, 100));
	VertexColors.Add(FColor::White);
	

	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);

	Triangles.Add(0);
	Triangles.Add(3);
	Triangles.Add(1);

	Triangles.Add(0);
	Triangles.Add(2);
	Triangles.Add(3);

	Triangles.Add(1);
	Triangles.Add(3);
	Triangles.Add(2);

	FRuntimeMeshTangent tangent = FRuntimeMeshTangent(1, 0, 0);
	
	for (int i = 0; i < Vertices.Num(); i++) {
		FRuntimeMeshVertexSimple packed_vertex = FRuntimeMeshVertexSimple(Vertices[i], VertexColors[i]);
		Packed_Vertices.Add(packed_vertex);
	}

	RuntimeMesh->CreateMeshSection(0, Packed_Vertices, Triangles);
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

