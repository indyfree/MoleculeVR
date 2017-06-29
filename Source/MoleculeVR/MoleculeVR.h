// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

class MoleculeVRModule : public FDefaultGameModuleImpl {

public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	void* AssimpDLL;
};

