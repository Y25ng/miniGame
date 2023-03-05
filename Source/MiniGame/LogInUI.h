// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LogInUI.generated.h"


UCLASS()
class MINIGAME_API ULogInUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// ���� UI�� �����ϰ� ȭ�鿡 ����ϴ� �Լ�
	void CreateUI();
};
