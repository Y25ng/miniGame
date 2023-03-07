// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraForMinimap.generated.h"


class UCameraComponent;
class USceneCaptureComponent2D;


/////////////////////////////////////////////////////////
// �̴ϸ��� ���� ī�޶� ������Ʈ�� ������ Actor Ŭ����
/////////////////////////////////////////////////////////
UCLASS()
class MINIGAME_API ACameraForMinimap : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = ( AllowPrivateAccess = "true" ) )
	UCameraComponent* FollowCamera;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = ( AllowPrivateAccess = "true" ) )
	USceneCaptureComponent2D* SceneCaptureComponent;

public:	
	// Sets default values for this actor's properties
	ACameraForMinimap();

	// Called every frame
	virtual void Tick( float DeltaTime ) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
