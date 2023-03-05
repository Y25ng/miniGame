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

	behavior_tree_Comp = CreateDefaultSubobject< UBehaviorTreeComponent>(TEXT("BehaviorComp")); // �����̺��Ʈ�� ��ü ����
	blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp")); // ������ ��ü ����

	// Setup_Perception_System();  // AI Pawn �⺻ �ɷ¿� ���� �ʱ�ȭ
}

void AMiniGameAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMiniGameAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMiniGameAIController::OnPossess(APawn* InPawn) // Pawn�� AI ��Ʈ�ѷ��� ������ �ϴ� �Լ�
{
	Super::OnPossess(InPawn);

	AMiniGameBot* Bot = Cast<AMiniGameBot>(InPawn);

	if (Bot && Bot->BotBehavior)
	{
		if (Bot->BotBehavior->BlackboardAsset)
		{
			blackboard->InitializeBlackboard(*Bot->BotBehavior->BlackboardAsset); // ������ �ʱ�ȭ
		}
		behavior_tree_Comp->StartTree(*(Bot->BotBehavior)); // �����̺��Ʈ�� �۵� ����
	}
}

FRotator AMiniGameAIController::GetControlRotation() const // ���� ȸ���� ��ȯ
{
	if (GetPawn() == nullptr)
		return FRotator(0.f, 0.f, 0.f);

	return FRotator(0.f, GetPawn()->GetActorRotation().Yaw, 0.f);
}

UBlackboardComponent* AMiniGameAIController::get_blackboard() const // ������ ��ȯ �Լ�
{
	return blackboard;
}
