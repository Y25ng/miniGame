// Copyright Epic Games, Inc. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MiniGameGameMode.generated.h"


class UUserWidget;
class AActor;


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
	bool bCreateDefaultPawn;
	bool bServerConnect;
	AActor* m_CameraActor;

public:
	AMiniGameGameMode();
	~AMiniGameGameMode();
	void SetCameraActor( AActor* cameraActor ) { m_CameraActor = cameraActor; }

	virtual void Tick(float deltaTime) override;

protected:
	virtual void BeginPlay() override;

};
