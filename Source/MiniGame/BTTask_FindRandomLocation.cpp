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
	NodeName = TEXT( "Find Random Location" ); // 비헤이비어트리에서의 노드 이름을 지정
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask( UBehaviorTreeComponent& owner_Comp, uint8* NodeMemory )
{
	auto const cont = Cast< AMiniGameAIController >( owner_Comp.GetAIOwner() ); // AI Controller
	auto const npc = cont->GetPawn(); // AI Controller의 조종을 받는 Pawn

	FVector const origin = npc->GetActorLocation(); // npc Pawn의 위치값
	FNavLocation loc;

	UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent( GetWorld() );
	
	bool tempFlag = nav_sys->GetRandomPointInNavigableRadius( origin, search_radius, loc, nullptr );

	if ( tempFlag )
	{
		cont->get_blackboard()->SetValueAsVector( bb_keys::target_location, loc.Location ); // 이동할 위치 지정
	}

	FinishLatentTask( owner_Comp, EBTNodeResult::Succeeded );
	return EBTNodeResult::Succeeded;
}
