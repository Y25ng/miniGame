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
	// 메인 UI를 생성하고 화면에 출력하는 함수
	void CreateUI();
};
