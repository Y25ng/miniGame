// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"


class UUniformGridPanel;
/**
 * 
 */
UCLASS()
class MINIGAME_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
		UUniformGridPanel* miniMap_GridPanel = nullptr;	

public:
	void NativeConstruct() override;

	UUniformGridPanel* GetMiniMap() { return miniMap_GridPanel; }
};
