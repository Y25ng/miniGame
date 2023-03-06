// Copyright Epic Games, Inc. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MiniGameCharacter.generated.h"


UCLASS( config=Game )
class AMiniGameCharacter : public ACharacter
{
private:

	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = ( AllowPrivateAccess = "true" ) )
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = ( AllowPrivateAccess = "true" ) )
		class UCameraComponent* FollowCamera;

	float m_PeriodSendToServer;
	float m_LerpTime;
	float m_XLocation;
	float m_YLocation;
	int32 m_OwnerIndex;

	FVector m_StartLocation;
	FVector m_TargetLocation;
	FVector m_TargetDirection;

	bool m_bRecvLocation;

public:
	AMiniGameCharacter();

	UFUNCTION()
		int32 GetColor() { return m_Color; }
	UFUNCTION()
		void SetColor( int32 colorNum ) { m_Color = colorNum; }

	void SetDefaultLocation( float x, float y );
	void SetOwnerIndex( int var ) { m_OwnerIndex = var; }
	void SetbRecvLocation( bool var ) { m_bRecvLocation = var; }
	void SetStartLocation( FVector var ) { m_StartLocation = var; }
	void SetTargetLocation( FVector var ) { m_TargetLocation = var; }
	void SetTargetDirection( FVector var ) { m_TargetDirection = var; }

	// �浹ü�� ������ �߻��� ȣ��
	virtual void NotifyActorBeginOverlap( AActor* OtherActor )override;
	virtual void NotifyHit( class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit ) override;


	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category=Camera )
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category=Camera )
		float BaseLookUpRate;


protected:

	UPROPERTY(EditAnywhere)
		int32 m_Color;

	UPROPERTY(EditAnywhere)
		FName NickName;

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward( float Value );

	/** Called for side to side input */
	void MoveRight( float Value );

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate( float Rate );

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate( float Rate );

	/** Handler for when a touch input begins. */
	void TouchStarted( ETouchIndex::Type FingerIndex, FVector Location );

	/** Handler for when a touch input stops. */
	void TouchStopped( ETouchIndex::Type FingerIndex, FVector Location );

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
