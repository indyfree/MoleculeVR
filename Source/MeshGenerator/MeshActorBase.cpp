// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshGenerator.h"
#include "MeshActorBase.h"


// Sets default values
AMeshActorBase::AMeshActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RuntimeMesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("Runtime Mesh"));
	RootComponent = RuntimeMesh;
}

void AMeshActorBase::CreateMesh(const std::string & filename) 
{
	ImportMesh(filename);
	SetVertexColorMaterial();
	RuntimeMesh->CreateMeshSection(0, Vertices, Triangles);
}

// Called when the game starts or when spawned
void AMeshActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeshActorBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AMeshActorBase::ImportMesh(const std::string & filename)
{

	MeshImporter import(filename);
	//TODO dont copy -> pointer or refs
	std::vector<float> vertices =  import.GetVertices();
	//TODO if normals exist
	std::vector<float> normals =  import.GetNormals();
	std::vector<uint32_t> faces =  import.GetFaces();
	std::vector<uint8_t> colors =  import.GetColors();

	FRuntimeMeshTangent tangent = FRuntimeMeshTangent(1, 0, 0);
	
	for (int i = 0; i <= vertices.size() - 3; i += 3) {
		FVector position = FVector(vertices[i], vertices[i + 1], vertices[i + 2]);
		FVector normal = FVector(normals[i], normals[i + 1], normals[i + 2]);
		FColor color = FColor(colors[i], colors[i + 1], colors[i + 2]);

		FRuntimeMeshVertexSimple packed_vertex = FRuntimeMeshVertexSimple(position, normal, tangent, color);
		Vertices.Add(packed_vertex);
	}

	for (int i = 0; i <= faces.size(); i += 3) {
		Triangles.Add(faces[i]);
		Triangles.Add(faces[i + 2]);
		Triangles.Add(faces[i + 1]);
	}
}
void AMeshActorBase::SetVertexColorMaterial()
{

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/VirtualReality/Materials/VertexColor.VertexColor'"));

	UMaterial* vertex_color_material = NULL;
	if (Material.Object != NULL)
	{
		vertex_color_material = (UMaterial*)Material.Object;
	}

	// Maybe later use for dynamic materials
	//UMaterialInstanceDynamic* dynamic_vertex_color_material = UMaterialInstanceDynamic::Create(vertex_color_material, NULL);

	RuntimeMesh->SetMaterial(0, vertex_color_material);
}
