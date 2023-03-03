// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


class UUserWidget;
class UMainUI;
class UWorld;


class MINIGAME_API UIManager
{
public:

	static UIManager& GetInstance()
	{
		static UIManager instance;
		return instance;
	}

	void CreateMainUI( UWorld* world );


private:
	UIManager();
	~UIManager();

	TSubclassOf< UUserWidget > MainUIClass;
	UUserWidget* MainUI;

};
