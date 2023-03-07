// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LobbyBottom.generated.h"


class UBoxComponent;
class UStaticMeshComponent;


UCLASS()
class MINIGAME_API ALobbyBottom : public AActor
{
	GENERATED_BODY()
	
private:
	// mesh
	UPROPERTY( VisibleAnywhere )
	UStaticMeshComponent* m_StaticMesh;

	// box �浹ü
	UPROPERTY( VisibleAnywhere )
	UBoxComponent* m_BoxCollision;

public:	
	// Sets default values for this actor's properties
	ALobbyBottom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
