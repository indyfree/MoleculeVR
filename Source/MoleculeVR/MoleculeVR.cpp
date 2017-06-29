// Fill out your copyright notice in the Description page of Project Settings.

#include "MoleculeVR.h"

IMPLEMENT_PRIMARY_GAME_MODULE( MoleculeVRModule, MoleculeVR, "MoleculeVR" );

void MoleculeVRModule::StartupModule()
{
	TCHAR* Path = TEXT("../../thirdParty/assimp/libraries/assimp.dll");
	AssimpDLL = FPlatformProcess::GetDllHandle(Path);
}

void MoleculeVRModule::ShutdownModule()
{
	FPlatformProcess::FreeDllHandle(AssimpDLL);
}
