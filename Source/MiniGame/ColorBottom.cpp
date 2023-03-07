// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorBottom.h"
#include "Components/BoxComponent.h" // box �浹ü ���
#include "Components/StaticMeshComponent.h" // mesh component ���
#include "GameFramework/Character.h" // UE4 ���� Character ���
#include "GameFramework/CharacterMovementComponent.h"
// #include "Kismet/KismetMathLibrary.h" // ���������� ���� ���
#include "MiniGameCharacter.h" // ������Ʈ ����Ʈ Character ���
#include "MiniGameGameMode.h" // ������Ʈ ����Ʈ GameMode ���
#include "Runtime/Engine/Classes/Engine/World.h" // ���� World ��ȯ�� ���� ���
#include "ActorManager.h"


// Sets default values
AColorBottom::AColorBottom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// box �浹ü
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

	// Ÿ�� ���� ��ȭ�� ���� ����� ���͸��� 
	static ConstructorHelpers::FObjectFinder< UMaterial > MaterialAsset_White( TEXT( "/Game/StarterContent/Materials/White" ) );
	static ConstructorHelpers::FObjectFinder< UMaterial > MaterialAsset_Red( TEXT( "/Game/StarterContent/Materials/Red" ) );
	static ConstructorHelpers::FObjectFinder< UMaterial > MaterialAsset_Blue( TEXT( "/Game/StarterContent/Materials/Blue" ) );
	static ConstructorHelpers::FObjectFinder< UMaterial > MaterialAsset_Yellow(TEXT("/Game/StarterContent/Materials/Yellow"));

	// key, value( int32, material )������ �����̳ʿ� ���� �߰�
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


	if ( ActorManager::GetInstance().GetColorBottom() == nullptr )
	{
		ActorManager::GetInstance().SetColorBottom( this );
	}
}


// Called when the game starts or when spawned
void AColorBottom::BeginPlay()
{
	Super::BeginPlay();

	if ( m_StaticMesh )
	{
		// Ÿ���� �ʱ� ������ ������� ����
		m_StaticMesh->SetMaterial(0, m_Material_Map[EColorNum::WHITE]);
		// Ÿ���� ���� ���� ���¸� ��Ÿ���� ������ �Ͼ���� �ǹ��ϴ� ��� �Ҵ�
		m_CurrentColor = EColorNum::WHITE;
	}

	ActorManager::GetInstance().PushBottom( m_BottomNumber, this );

	// m_OriginLocation = GetActorLocation();
	// m_ElevateLocation = m_OriginLocation + FVector( 0.0f, 0.0f, 200.0f );
}

// Called every frame
void AColorBottom::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// m_BottomDeltaTime += DeltaTime;
}

// Ÿ���� �ٸ� ��ü�� �浹�� �߻����� �� �ڵ����� ȣ��
void AColorBottom::NotifyActorBeginOverlap( AActor* OtherActor )
{
	/*
	AMiniGameCharacter* tempCharacter = Cast< AMiniGameCharacter >( OtherActor );

	if ( tempCharacter == nullptr )
		return;

	int32 tempCharacterColor = tempCharacter->GetColor();

	if ( tempCharacterColor == m_CurrentColor )
		return;

	// Ÿ�� ���� ���� �� ���� ���� ���� �Ҵ�
	ChangeColor( tempCharacterColor );
	m_CurrentColor = tempCharacterColor;

	/*
	if ( m_bElevate == false )
	{
		GetWorldTimerManager().SetTimer(BottomTimerHandle, this, &AColorBottom::OnElevate, 0.03f, true);
	}
	*/
}

// ���� Ÿ���� ���͸����� �ٲ��ִ� �Լ�
void AColorBottom::ChangeColor( int32 colorNum )
{
	m_StaticMesh->SetMaterial( 0, m_Material_Map[ colorNum ] );
}

/*
// �浹ü�� �������� ������ ȣ��
void AColorBottom::NotifyActorEndOverlap( AActor* OtherActor )
{
	if ( m_bElevate == true )
	{
		GetWorldTimerManager().SetTimer( BottomTimerHandle, this, &AColorBottom::OffElevate, 0.03f, true );
	}
}
*/

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
