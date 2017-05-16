// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshGenerator.h"
#include "Menu.h"


// Sets default values
AMenu::AMenu()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMenu::BeginPlay()
{
	Super::BeginPlay();
	
	vector<string> paths = MoleculePicker::FindMeshesInFolder(TCHAR_TO_UTF8(*DirectoryPath));
	for (string path : paths) {
		MolPaths.Add(FString(path.c_str()));
	}
}

// Called every frame
void AMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

