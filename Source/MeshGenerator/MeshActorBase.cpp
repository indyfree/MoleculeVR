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

void AMeshActorBase::CreateMesh(const char* path)
{
	ImportMesh(path);
	SetVertexColorMaterial(0);
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

void AMeshActorBase::ImportMesh(const char* path)
{
	MeshImporter import(path);
	vector<FVector> vertices =  import.GetVertices();
	vector<uint32_t> faces =  import.GetFaces();
	vector<FColor> colors =  import.GetColors();
	vector<FVector> normals =  import.GetNormals();

	if (vertices.size() != 0 && faces.size() != 0) {

		FRuntimeMeshVertexSimple packed_vertex;
		FRuntimeMeshTangent tangent;
		for (int i = 0; i < vertices.size(); ++i) {
			packed_vertex = FRuntimeMeshVertexSimple(vertices[i], normals[i], tangent, colors[i]);
			Vertices.Add(packed_vertex);
		}

		for (int i = 0; i <= faces.size(); i += 3) {
			Triangles.Add(faces[i]);
			Triangles.Add(faces[i + 1]);
			Triangles.Add(faces[i + 2]);
		}
	}
}
void AMeshActorBase::SetVertexColorMaterial(int section)
{

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/VirtualReality/Materials/VertexColor.VertexColor'"));

	UMaterial* vertex_color_material = NULL;
	if (Material.Object != NULL)
	{
		vertex_color_material = (UMaterial*)Material.Object;
	}

	// Maybe later use for dynamic materials
	//UMaterialInstanceDynamic* dynamic_vertex_color_material = UMaterialInstanceDynamic::Create(vertex_color_material, NULL);

	RuntimeMesh->SetMaterial(section, vertex_color_material);
}
