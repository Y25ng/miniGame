// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


class UUserWidget;
class UMainUI;
class ULogInUI;
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
	void CreateLogInUI(UWorld* world);

	TSubclassOf< UUserWidget > GetMainUIClass() { return MainUIClass; }

private:
	UIManager();
	~UIManager();

	// � �����̳ʷ� �������� ����غ���
	TSubclassOf< UUserWidget > MainUIClass;
	UUserWidget* MainUIWidget;

	TSubclassOf< UUserWidget > LogInUIClass;
	UUserWidget* LogInUIWidget;

};
