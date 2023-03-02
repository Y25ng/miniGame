// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameBot.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

AMiniGameBot::AMiniGameBot()
{
	setup_stimulus();// AI 구현에 따른 자극을 주는 함수
}

void AMiniGameBot::setup_stimulus() // AI 구현에 따른 자극을 주는 함수
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>( TEXT( "stimulus" ) );
	stimulus->RegisterForSense( TSubclassOf<UAISense_Sight>() );
	stimulus->RegisterWithPerceptionSystem();
}