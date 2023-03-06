// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"


// class AActor;
class UImage;
// class UMaterial;


UCLASS()
class MINIGAME_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

private:
	// 미니맵을 보여줄 이미지
	UPROPERTY( meta = ( BindWidget ) )
		UImage* miniMap_Image = nullptr;

public:
	UMainUI( const FObjectInitializer& ObjectInitializer );
	void NativeConstruct() override;

	// 메인 UI를 생성하고 화면에 출력하는 함수
	void CreateUI();

	// 미니맵 이미지를 갱신해줄 함수
	// void UpdateMiniMap( AActor* cameraActor );
};
