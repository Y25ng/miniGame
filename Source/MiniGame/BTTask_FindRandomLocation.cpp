// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "BehaviorTree/BTNode.h" 
#include "BehaviorTree/BehaviorTreeComponent.h" 
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "NavigationSystem.h"
#include "blackboard_keys.h"
#include "MiniGameAIController.h"


UBTTask_FindRandomLocation::UBTTask_FindRandomLocation( FObjectInitializer const& object_initializer )
{
	NodeName = TEXT( "Find Random Location" ); // �����̺��Ʈ�������� ��� �̸��� ����
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask( UBehaviorTreeComponent& owner_Comp, uint8* NodeMemory )
{
	auto const cont = Cast< AMiniGameAIController >( owner_Comp.GetAIOwner() ); // AI Controller
	auto const npc = cont->GetPawn(); // AI Controller�� ������ �޴� Pawn

	FVector const origin = npc->GetActorLocation(); // npc Pawn�� ��ġ��
	FNavLocation loc;

	UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent( GetWorld() );
	
	bool tempFlag = nav_sys->GetRandomPointInNavigableRadius( origin, search_radius, loc, nullptr );

	if ( tempFlag )
	{
		cont->get_blackboard()->SetValueAsVector( bb_keys::target_location, loc.Location ); // �̵��� ��ġ ����
	}

	FinishLatentTask( owner_Comp, EBTNodeResult::Succeeded );
	return EBTNodeResult::Succeeded;
}
