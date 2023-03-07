// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include "Components/BoxComponent.h" // box 충돌체 헤더
#include "Components/StaticMeshComponent.h" // mesh component 헤더
#include "MiniGameCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// box 충돌체
	m_BoxCollision = CreateDefaultSubobject< UBoxComponent >( TEXT( "BoxObj" ) );

	if ( m_BoxCollision )
	{
		m_BoxCollision->SetupAttachment( RootComponent );
		RootComponent = m_BoxCollision;
	}

	// mesh
	m_StaticMesh = CreateDefaultSubobject< UStaticMeshComponent >( TEXT( "MeshObj" ) );

	if ( m_StaticMesh )
	{
		m_StaticMesh->SetupAttachment( RootComponent );
	}
}

void AWall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWall::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);
}
