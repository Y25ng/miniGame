// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "MiniGameAIController.generated.h"


class UBehaviorTree;
class UBehaviorTreeComponent;
class UBlackboardComponent;
// class UAISenseConfig_Sight;


UCLASS(config = Game)
class MINIGAME_API AMiniGameAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	AMiniGameAIController(FObjectInitializer const& object_initializer);

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;  // Pawn이 AI Controller를 가지게 하는 함수
	virtual void Tick(float DeltaSeconds) override;
	virtual FRotator GetControlRotation() const override; // Pawn의 FRotator 정보를 반환 

	class UBlackboardComponent* get_blackboard() const; // 블랙보드 반환 함수

private:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* behavior_tree_Comp; // 비헤이비어트리 컴퍼넌트
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* btree; // 비헤이비어트리

	UBlackboardComponent* blackboard; // 블랙보드

};
