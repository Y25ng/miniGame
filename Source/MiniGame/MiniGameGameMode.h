// Copyright Epic Games, Inc. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "MiniGameGameMode.generated.h"


class UUserWidget;

// Ÿ�� ������ �ǹ��ϴ� ������ ������ �Ҵ��� enum��
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
	TSubclassOf<class UUserWidget>MainUI_WidgetBPClass;
	UUserWidget* MainUI_Widget;

public:
	AMiniGameGameMode();

	UUserWidget* GetMainUI() { return MainUI_Widget; }

};


