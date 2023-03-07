// Fill out your copyright notice in the Description page of Project Settings.
 

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColorBottom.generated.h"


class UBoxComponent;
class UMaterial;
class UStaticMeshComponent;


/////////////////////////////////////////////////////////
// ��ü �ٴ� �������� 6x6 ���� �� �� ������ ������ ������Ʈ
/////////////////////////////////////////////////////////
UCLASS()
class MINIGAME_API AColorBottom : public AActor
{
	GENERATED_BODY()
	
private:
	// ���� Ÿ�� ����
	UPROPERTY( VisibleAnywhere )
	int32 m_CurrentColor;

	// mesh
	UPROPERTY( VisibleAnywhere )
	UStaticMeshComponent* m_StaticMesh;

	// box �浹ü
	UPROPERTY( VisibleAnywhere )
	UBoxComponent* m_BoxCollision;

	// matrial �����̳�
	UPROPERTY( VisibleAnywhere )
	TMap< int32, UMaterial* > m_Material_Map;

	/*
	// Ÿ���� �ö��ִ� �������� �ƴ��� ���θ� �Ҵ�޴� ����
	UPROPERTY(VisibleAnywhere)
		bool m_bElevate;

	FVector m_OriginLocation;
	FVector m_ElevateLocation;

	float m_BottomDeltaTime;

	FTimerHandle BottomTimerHandle;
	*/

public:	
	// Sets default values for this actor's properties
	AColorBottom();

	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	// �浹ü�� ������ �߻��� ȣ��
	virtual void NotifyActorBeginOverlap( AActor* OtherActor )override; 

	// Ÿ�� ������ �������� �Լ�
	void ChangeColor( int32 colorNum );

	int32 GetBottomNumber() { return m_BottomNumber; }

	// �浹ü�� �������� ������ ȣ��
	// virtual void NotifyActorEndOverlap(AActor* OtherActor)override;
	// void OnElevate();
	// void OffElevate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ���� Ÿ�� ����
	UPROPERTY( EditAnywhere )
		int32 m_BottomNumber;
};
