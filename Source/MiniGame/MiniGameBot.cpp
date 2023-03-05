// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameBot.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"


AMiniGameBot::AMiniGameBot()
{
	setup_stimulus();// AI ������ ���� �ڱ��� �ִ� �Լ�
}

void AMiniGameBot::setup_stimulus() // AI ������ ���� �ڱ��� �ִ� �Լ�
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>( TEXT( "stimulus" ) );
	stimulus->RegisterForSense( TSubclassOf<UAISense_Sight>() );
	stimulus->RegisterWithPerceptionSystem();
}

void AMiniGameBot::NotifyHit( UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit )
{
	AMiniGameCharacter::NotifyHit( MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit );
}