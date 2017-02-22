// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshGenerator.h"
#include "MeshImporter.h"
#include "StabiloMesh.h"


// Sets default values
AStabiloMesh::AStabiloMesh()
{	
	PrimaryActorTick.bCanEverTick = true;

	RuntimeMesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("Runtime Mesh"));
	RootComponent = RuntimeMesh;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	TArray<FVector> Vertices;
	TArray<FVector> Normals;
	TArray<FRuntimeMeshTangent> Tangents;
	TArray<FColor> VertexColors;
	TArray<FVector2D> TextureCoordinates;
	TArray<int32> Triangles;

	MeshImporter import("c:/users/tobias/mesh/stabilo.ply");
	std::vector<float> vertices =  import.GetVertices();
	std::vector<float> normals =  import.GetNormals();
	std::vector<uint32_t> faces =  import.GetFaces();
	std::vector<uint8_t> colors =  import.GetColors();

	// First vertex
	Vertices.Add(FVector(0, 100, 100));
	Normals.Add(FVector(0, 0, 1));
	Tangents.Add(FRuntimeMeshTangent(0, -1, 0));
	VertexColors.Add(FColor::White);
	TextureCoordinates.Add(FVector2D(0, 0));

	// Second vertex
	Vertices.Add(FVector(100, 100, 0));
	Normals.Add(FVector(0, 0, 1));
	Tangents.Add(FRuntimeMeshTangent(0, -1, 0));
	VertexColors.Add(FColor::White);
	TextureCoordinates.Add(FVector2D(0, 1));

	// Third vertex
	Vertices.Add(FVector(100, 0, 0));
	Normals.Add(FVector(0, 0, 1));
	Tangents.Add(FRuntimeMeshTangent(0, -1, 0));
	VertexColors.Add(FColor::White);
	TextureCoordinates.Add(FVector2D(1, 1));

	// Fourth vertex
	Vertices.Add(FVector(0, 0, 0));
	Normals.Add(FVector(0, 0, 1));
	Tangents.Add(FRuntimeMeshTangent(0, -1, 0));
	VertexColors.Add(FColor::White);
	TextureCoordinates.Add(FVector2D(1, 0));

	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);
	Triangles.Add(0);
	Triangles.Add(2);
	Triangles.Add(3);

	RuntimeMesh->CreateMeshSection(0, Vertices, Triangles, Normals, TextureCoordinates, VertexColors, Tangents);
}

// Called when the game starts or when spawned
void AStabiloMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStabiloMesh::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

