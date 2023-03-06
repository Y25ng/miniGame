// Copyright Epic Games, Inc. All Rights Reserved.


#include "MiniGameCharacter.h"
#include "MiniGameGameMode.h" // ������Ʈ ����Ʈ GameMode ���
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h" // ī�޶� ���
#include "Components/CapsuleComponent.h" // ĳ���� �浹ü�� ����� ĸ�� ���
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Wall.h"
#include "UserManager.h"
#include "ServerManager.h"
#include "Protocol.h"


AMiniGameCharacter::AMiniGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator( 0.0f, 540.0f, 0.0f ); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject< USpringArmComponent >( TEXT( "CameraBoom" ) );
	CameraBoom->SetupAttachment( RootComponent );
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject< UCameraComponent >( TEXT( "FollowCamera" ) );
	FollowCamera->SetupAttachment( CameraBoom, USpringArmComponent::SocketName ); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	m_XLocation = GetActorLocation().X;
	m_YLocation = GetActorLocation().Y;
	m_PeriodSendToServer = 0.0f;
	m_LerpTime = 0.0f;
	m_GameTimeSec = 0;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

AMiniGameCharacter::~AMiniGameCharacter()
{
	if ( m_OwnerIndex == UserManager::GetInstance().GetMainCharacterIndex() )
	{
		ServerManager::GetInstance().ShutDown();
	}
}

void AMiniGameCharacter::SetDefaultLocation( float x, float y )
{
	m_XLocation = x;
	m_YLocation = y;

	float tempZ = GetActorLocation().Z;

	FVector targetLocation = FVector( x, y, tempZ );

	SetActorLocation( targetLocation );
}

void AMiniGameCharacter::BeginPlay()
{
	Super::BeginPlay();
*
	if ( NickName.ToString() == TEXT( "Default" ) ) // �÷��̾ ������ ĳ����
	{
		ServerManager::GetInstance().SetCharacter( this );
	}
	else if ( NickName.ToString() == TEXT( "second" ) ) // �÷��̾�� ����� ĳ����1
	{
		ServerManager::GetInstance().SetCharacter2( this );
	}
	else if ( NickName.ToString() == TEXT( "third" ) ) // �÷��̿��� ����� ĳ����2
	{
		ServerManager::GetInstance().SetCharacter3( this );
	}

}

void AMiniGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_PeriodSendToServer += DeltaTime;

	float currentXLocation = GetActorLocation().X;
	float currentYLocation = GetActorLocation().Y;
	

	if ( ServerManager::GetInstance().GetbGameStart() && m_PeriodSendToServer >= 0.05f 
		&& static_cast< int >( currentXLocation ) != static_cast< int >( m_XLocation )
		&& static_cast< int >( currentYLocation ) != static_cast< int >( m_YLocation ) )
	{
		m_PeriodSendToServer = 0.0f;
		m_XLocation = currentXLocation;
		m_YLocation = currentYLocation;

		if ( UserManager::GetInstance().GetMainCharacterIndex() == m_OwnerIndex )
		{
			Packet::Move objMove( m_OwnerIndex, ClientToServer::MOVE );

			objMove.x = m_XLocation;
			objMove.y = m_YLocation;
			objMove.directionX = GetActorForwardVector().X;
			objMove.directionY = GetActorForwardVector().Y;
			objMove.speed = GetVelocity().Size();

			ServerManager::GetInstance().SendPacket( ClientToServer::MOVE, &objMove);
		}
	}

	if ( m_bRecvLocation )
	{
		m_LerpTime += DeltaTime;
		FVector LerpedLocation = FMath::Lerp( m_StartLocation, m_TargetLocation, m_LerpTime );

		SetActorLocation( LerpedLocation );

		FRotator targetRotation = m_TargetDirection.Rotation();
		SetActorRotation( FMath::RInterpTo(GetActorRotation(), targetRotation, GetWorld()->GetDeltaSeconds(), 40.f ));
		
		if ( m_LerpTime >= 1.0f )
		{
			m_bRecvLocation = false;
			m_LerpTime = 0.0f;
		}
	}	
}	

//////////////////////////////////////////////////////////////////////////
// Input

void AMiniGameCharacter::SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent )
{
	// Set up gameplay key bindings
	check( PlayerInputComponent );
	PlayerInputComponent->BindAction( "Jump", IE_Pressed, this, &ACharacter::Jump );
	PlayerInputComponent->BindAction( "Jump", IE_Released, this, &ACharacter::StopJumping );

	PlayerInputComponent->BindAxis( "MoveForward", this, &AMiniGameCharacter::MoveForward );
	PlayerInputComponent->BindAxis( "MoveRight", this, &AMiniGameCharacter::MoveRight );

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis( "Turn", this, &APawn::AddControllerYawInput );
	PlayerInputComponent->BindAxis( "TurnRate", this, &AMiniGameCharacter::TurnAtRate );
	PlayerInputComponent->BindAxis( "LookUp", this, &APawn::AddControllerPitchInput );
	PlayerInputComponent->BindAxis( "LookUpRate", this, &AMiniGameCharacter::LookUpAtRate );

	// handle touch devices
	PlayerInputComponent->BindTouch( IE_Pressed, this, &AMiniGameCharacter::TouchStarted );
	PlayerInputComponent->BindTouch( IE_Released, this, &AMiniGameCharacter::TouchStopped );

	// VR headset functionality
	PlayerInputComponent->BindAction( "ResetVR", IE_Pressed, this, &AMiniGameCharacter::OnResetVR );
}


void AMiniGameCharacter::NotifyActorBeginOverlap( AActor* OtherActor )
{
	AMiniGameCharacter* otherCharacter = nullptr;
	otherCharacter = Cast< AMiniGameCharacter >( OtherActor );
}

void AMiniGameCharacter::NotifyHit( UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit )
{
	Super::NotifyHit( MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit );

	if ( Other->IsA( AWall::StaticClass() ) )
	{
		// �浹 �ð�
		float HitTime = Hit.Time;

		// �浹�� Actor�� �ӵ� ����
		FVector OtherActorVelocity = Other->GetVelocity();

		// Character�� ���� �ӵ� ����
		FVector PreviousVelocity = GetVelocity();

		// �浹 ������ ���� ����
		FVector tempHitNormal = Hit.ImpactNormal;

		// ���� �ӵ� ���Ϳ� �浹 ������ ���� ���͸� ����ȭ
		PreviousVelocity.Normalize();
		tempHitNormal.Normalize();

		// ���� �ӵ� ���Ϳ� ���� ������ ������ ���
		float DotProduct = FVector::DotProduct(tempHitNormal, PreviousVelocity);

		// �������� ����Ͽ� Character�� �浹 �������� �����ִ� Actor�� ��� �������� ƨ���� ������ �ϴ��� ���
		FVector ReflectedVelocity = PreviousVelocity - 2.0f * DotProduct * tempHitNormal;

		// ���ο� �ӵ� ���� ����
		float ImpulseStrength = 10000.0f;
		GetCharacterMovement()->AddImpulse(ReflectedVelocity * ImpulseStrength, true);

		return;
	}

	AMiniGameCharacter* otherCharacter = nullptr;
	otherCharacter = Cast< AMiniGameCharacter >( Other );

	if (otherCharacter)
	{
		// �浹�� ��ġ���� ƨ���� ������ ������ ���
		FVector AwayFromOther = ( GetActorLocation() - otherCharacter->GetActorLocation() ).GetSafeNormal();

		// ƨ���� ������ ���� ũ�⸦ ����
		float BounceForceMagnitude = 5000.f;

		// ���� ����Ͽ� AddImpulse �Լ��� ����Ͽ� ƨ���� �������� ó��
		FVector BounceForce = AwayFromOther * BounceForceMagnitude;
		GetCharacterMovement()->AddImpulse( BounceForce, true );
	}
}

void AMiniGameCharacter::OnResetVR()
{
	// If MiniGame is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in MiniGame.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMiniGameCharacter::TouchStarted( ETouchIndex::Type FingerIndex, FVector Location )
{
	Jump();
}

void AMiniGameCharacter::TouchStopped( ETouchIndex::Type FingerIndex, FVector Location )
{
	StopJumping();
}

void AMiniGameCharacter::TurnAtRate( float Rate )
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput( Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() );
}

void AMiniGameCharacter::LookUpAtRate( float Rate )
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput( Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() );
}

void AMiniGameCharacter::MoveForward( float Value )
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation( 0, Rotation.Yaw, 0 );

		// get forward vector
		const FVector Direction = FRotationMatrix( YawRotation ).GetUnitAxis( EAxis::X );
		AddMovementInput( Direction, Value );
	}
}

void AMiniGameCharacter::MoveRight( float Value )
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation( 0, Rotation.Yaw, 0 );
	 
		// get right vector 
		const FVector Direction = FRotationMatrix( YawRotation ).GetUnitAxis( EAxis::Y );
		// add movement in that direction
		AddMovementInput( Direction, Value );
	}
}

