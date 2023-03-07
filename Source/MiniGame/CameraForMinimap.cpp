// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraForMinimap.h"
#include "Camera/CameraComponent.h" // ī�޶� ������Ʈ�� ���� ���
#include "Components/SceneCaptureComponent2D.h" // ī�޶� ��� ĸ�� ������Ʈ ���


// Sets default values
ACameraForMinimap::ACameraForMinimap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject< UCameraComponent >( TEXT( "FollowCamera" ) );
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void ACameraForMinimap::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACameraForMinimap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
