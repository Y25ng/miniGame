// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "MiniGameBot.h"


AMiniGameAIController::AMiniGameAIController(FObjectInitializer const& object_initializer)
{
	PrimaryActorTick.bCanEverTick = true;

	behavior_tree_Comp = CreateDefaultSubobject< UBehaviorTreeComponent>(TEXT("BehaviorComp")); // 비헤이비어트리 객체 생성
	blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp")); // 블랙보드 객체 생성

	// Setup_Perception_System();  // AI Pawn 기본 능력에 대한 초기화
}

void AMiniGameAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMiniGameAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMiniGameAIController::OnPossess(APawn* InPawn) // Pawn이 AI 컨트롤러를 가지게 하는 함수
{
	Super::OnPossess(InPawn);

	AMiniGameBot* Bot = Cast<AMiniGameBot>(InPawn);

	if (Bot && Bot->BotBehavior)
	{
		if (Bot->BotBehavior->BlackboardAsset)
		{
			blackboard->InitializeBlackboard(*Bot->BotBehavior->BlackboardAsset); // 블랙보드 초기화
		}
		behavior_tree_Comp->StartTree(*(Bot->BotBehavior)); // 비헤이비어트리 작동 시작
	}
}

FRotator AMiniGameAIController::GetControlRotation() const // 현재 회전값 반환
{
	if (GetPawn() == nullptr)
		return FRotator(0.f, 0.f, 0.f);

	return FRotator(0.f, GetPawn()->GetActorRotation().Yaw, 0.f);
}

UBlackboardComponent* AMiniGameAIController::get_blackboard() const // 블랙보드 반환 함수
{
	return blackboard;
}
