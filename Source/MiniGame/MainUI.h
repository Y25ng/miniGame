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
	// �̴ϸ��� ������ �̹���
	UPROPERTY( meta = ( BindWidget ) )
		UImage* miniMap_Image = nullptr;

public:
	UMainUI( const FObjectInitializer& ObjectInitializer );
	void NativeConstruct() override;

	// ���� UI�� �����ϰ� ȭ�鿡 ����ϴ� �Լ�
	void CreateUI();

	// �̴ϸ� �̹����� �������� �Լ�
	// void UpdateMiniMap( AActor* cameraActor );
};
