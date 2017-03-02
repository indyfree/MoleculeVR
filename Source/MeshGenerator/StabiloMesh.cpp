// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshGenerator.h"
#include "MeshImporter.h"
#include "StabiloMesh.h"


UPROPERTY(EditAnywhere)
UMaterialInterface* Material;

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
	//TODO dont copy -> pointer or refs
	std::vector<float> vertices =  import.GetVertices();
	std::vector<float> normals =  import.GetNormals();
	std::vector<uint32_t> faces =  import.GetFaces();
	std::vector<uint8_t> colors =  import.GetColors();

	for (int i = 0; i < vertices.size() - 3; i += 3) {
		Vertices.Add(FVector(vertices[i], vertices[i + 1], vertices[i + 2]));
		VertexColors.Add(FColor(colors[i], colors[i+1], colors[i+2]));
	}

	for (int i = 0; i < faces.size(); ++i) {
		Triangles.Add(faces[i]);
	}


	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/VirtualReality/Materials/VertexColor.VertexColor'"));

	UMaterial* vertex_color_material = NULL;
	if (Material.Object != NULL)
	{
		vertex_color_material = (UMaterial*)Material.Object;
	}
	// Maybe later use for dynamic materials
	//UMaterialInstanceDynamic* dynamic_vertex_color_material = UMaterialInstanceDynamic::Create(vertex_color_material, NULL);

	RuntimeMesh->CreateMeshSection(0, Vertices, Triangles, Normals, TextureCoordinates, VertexColors, Tangents);
	RuntimeMesh->SetMaterial(0, vertex_color_material);
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

