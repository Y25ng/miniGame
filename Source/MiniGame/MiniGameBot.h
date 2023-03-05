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
		class UBehaviorTree* BotBehavior; // ���� �����̺�� Ʈ��

	UAIPerceptionStimuliSourceComponent* stimulus;
	void setup_stimulus(); // AI ������ ���� �ڱ��� �ִ� �Լ�	

	virtual void NotifyHit( class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit ) override;
};
