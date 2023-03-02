// Copyright Epic Games, Inc. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MiniGameGameMode.generated.h"


class UUserWidget;


// 타일 색깔을 의미하는 정수형 변수에 할당할 enum값
enum EColorNum
{
	WHITE = 0,
	RED,
	BLUE,
	YELLOW,
	END_COLORNUM,
};


UCLASS( minimalapi )
class AMiniGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	// 게임의 Main UI 블루프린트의 부모 클래스 객체
	TSubclassOf<class UUserWidget>MainUI_WidgetBPClass;
	UUserWidget* MainUI_Widget;

public:
	AMiniGameGameMode();

	virtual void Tick(float deltaTime) override;
	UUserWidget* GetMainUI() { return MainUI_Widget; }

};



