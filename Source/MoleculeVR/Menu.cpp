// Fill out your copyright notice in the Description page of Project Settings.

#include "MoleculeVR.h"
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
	vector<string> paths = FileFinder::FindFilesInFolder(TCHAR_TO_UTF8(*DirectoryPath), TCHAR_TO_UTF8(*FileExtension));
	for (string path : paths) {
		MoleculePaths.Add(FString(path.c_str()));
	}

	Super::BeginPlay();
}

// Called every frame
void AMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

