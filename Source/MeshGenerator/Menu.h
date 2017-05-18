// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MoleculePicker.h"
#include "Menu.generated.h"

UCLASS()
class MESHGENERATOR_API AMenu : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=MoleculeMenu)
	FString DirectoryPath = "d:/tobi/mesh/";
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=MoleculeMenu)
	FString FileExtension = ".dae";

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> MoleculePaths;

	// Sets default values for this actor's properties
	AMenu();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
};
