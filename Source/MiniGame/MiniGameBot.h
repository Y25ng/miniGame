// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGameCharacter.h"
#include "MiniGameBot.generated.h"


class UBehaviorTree;
class UAIPerceptionStimuliSourceComponent;


UCLASS()
class MINIGAME_API AMiniGameBot : public AMiniGameCharacter
{
	GENERATED_BODY()

public:

	AMiniGameBot();

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* BotBehavior; // 적의 비헤이비어 트리

	UAIPerceptionStimuliSourceComponent* stimulus;
	void setup_stimulus(); // AI 구현에 따른 자극을 주는 함수
	
};
