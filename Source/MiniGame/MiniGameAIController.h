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
	virtual void OnPossess(APawn* InPawn) override;  // Pawn�� AI Controller�� ������ �ϴ� �Լ�
	virtual void Tick(float DeltaSeconds) override;
	virtual FRotator GetControlRotation() const override; // Pawn�� FRotator ������ ��ȯ 

	class UBlackboardComponent* get_blackboard() const; // ������ ��ȯ �Լ�

private:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* behavior_tree_Comp; // �����̺��Ʈ�� ���۳�Ʈ
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* btree; // �����̺��Ʈ��

	UBlackboardComponent* blackboard; // ������

};
