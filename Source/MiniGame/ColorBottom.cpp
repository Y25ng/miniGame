// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorBottom.h"
#include "Components/BoxComponent.h" // box 충돌체 헤더
#include "Components/StaticMeshComponent.h" // mesh component 헤더
#include "GameFramework/Character.h" // UE4 제공 Character 헤더
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h" // 선형보간을 위한 헤더
#include "MiniGameCharacter.h" // 프로젝트 디폴트 Character 헤더
#include "MiniGameGameMode.h" // 프로젝트 디폴트 GameMode 헤더
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/UniformGridPanel.h"
#include "Widgets/Images/SImage.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.h"


// Sets default values
AColorBottom::AColorBottom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// box 충돌체
	m_BoxCollision = CreateDefaultSubobject< UBoxComponent >(TEXT("BoxObj"));

	if ( m_BoxCollision )
	{
		m_BoxCollision->SetupAttachment( RootComponent );
		RootComponent = m_BoxCollision;
	}

	// mesh
	m_StaticMesh = CreateDefaultSubobject< UStaticMeshComponent >( TEXT( "MeshObj" ) );
	
	if( m_StaticMesh )
		m_StaticMesh->SetupAttachment( RootComponent );

	static ConstructorHelpers::FObjectFinder< UMaterial > MaterialAsset_White( TEXT( "/Game/StarterContent/Materials/White" ) );
	static ConstructorHelpers::FObjectFinder< UMaterial > MaterialAsset_Red( TEXT( "/Game/StarterContent/Materials/Red" ) );
	static ConstructorHelpers::FObjectFinder< UMaterial > MaterialAsset_Blue( TEXT( "/Game/StarterContent/Materials/Blue" ) );
	static ConstructorHelpers::FObjectFinder< UMaterial > MaterialAsset_Yellow(TEXT("/Game/StarterContent/Materials/Yellow"));

	if ( MaterialAsset_White.Succeeded() )
		m_Material_Map.Add( EColorNum::WHITE ) = MaterialAsset_White.Object;
	else
		m_Material_Map.Add( EColorNum::WHITE ) = nullptr;

	if ( MaterialAsset_Red.Succeeded() )
		m_Material_Map.Add( EColorNum::RED ) = MaterialAsset_Red.Object;
	else
		m_Material_Map.Add( EColorNum::RED ) = nullptr;

	if ( MaterialAsset_Blue.Succeeded() )
		m_Material_Map.Add( EColorNum::BLUE ) = MaterialAsset_Blue.Object;
	else
		m_Material_Map.Add( EColorNum::BLUE ) = nullptr;

	if (MaterialAsset_Yellow.Succeeded())
		m_Material_Map.Add(EColorNum::YELLOW) = MaterialAsset_Yellow.Object;
	else
		m_Material_Map.Add(EColorNum::YELLOW) = nullptr;

	m_CurrentColor = EColorNum::WHITE;
	// m_bElevate = false;
	// m_BottomDeltaTime = 0.0f;
}


// Called when the game starts or when spawned
void AColorBottom::BeginPlay()
{
	Super::BeginPlay();

	if ( m_StaticMesh )
	{
		// 타일의 초기 색깔을 흰색으로 설정
		m_StaticMesh->SetMaterial(0, m_Material_Map[EColorNum::WHITE]);
	}

	// m_OriginLocation = GetActorLocation();
	// m_ElevateLocation = m_OriginLocation + FVector( 0.0f, 0.0f, 200.0f );
}

// Called every frame
void AColorBottom::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// m_BottomDeltaTime += DeltaTime;

}

void AColorBottom::NotifyActorBeginOverlap( AActor* OtherActor )
{
	AMiniGameCharacter* tempCharacter = Cast< AMiniGameCharacter >( OtherActor );
	int32 tempColor = tempCharacter->GetColor();

	if ( tempCharacter && (tempColor != m_CurrentColor) )
	{
		ChangeColor( tempColor );
		m_CurrentColor = tempColor;	

		UWorld* world = GetWorld();

		if (world)
		{
			AMiniGameGameMode* gameMode = Cast< AMiniGameGameMode >(world->GetAuthGameMode());
			if (gameMode)
			{
			}

		}
	}

	/*
	if ( m_bElevate == false )
	{
		GetWorldTimerManager().SetTimer(BottomTimerHandle, this, &AColorBottom::OnElevate, 0.03f, true);
	}
	*/

}

/*
// 충돌체에 오버랩이 끝날시 호출
void AColorBottom::NotifyActorEndOverlap( AActor* OtherActor )
{
	if ( m_bElevate == true )
	{
		GetWorldTimerManager().SetTimer( BottomTimerHandle, this, &AColorBottom::OffElevate, 0.03f, true );
	}
}
*/

void AColorBottom::ChangeColor( int32 colorNum )
{
	m_StaticMesh->SetMaterial( 0, m_Material_Map[ colorNum ] );
}

/*
void AColorBottom::OnElevate()
{
	// if (this->GetActorLabel() == labelStr)

	if ( m_bElevate == false )
	{
		m_bElevate = true;
		m_BottomDeltaTime = 0.0f;
	}

	FVector targetLocation = GetActorLocation();
	targetLocation = m_OriginLocation + FVector( 0, 0, FMath::Lerp( 0.0f, 200.0f, m_BottomDeltaTime ) );
	SetActorLocation( targetLocation );
	
	if ( m_BottomDeltaTime > 1.0f  )
	{
		GetWorldTimerManager().ClearTimer( BottomTimerHandle );
	}
}

void AColorBottom::OffElevate()
{
	if ( m_bElevate == true )
	{
		m_bElevate = false;
		m_BottomDeltaTime = 0.0f;
	}

	FVector targetLocation = GetActorLocation();
	targetLocation = m_ElevateLocation + FVector( 0, 0, FMath::Lerp( 0.0f, -200.0f, m_BottomDeltaTime ) );
	SetActorLocation( targetLocation );

	if ( m_BottomDeltaTime > 1.0f )
	{
		GetWorldTimerManager().ClearTimer( BottomTimerHandle );
	}
}
*/

