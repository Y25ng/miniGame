// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
// #include "Camera/CameraComponent.h" // ī�޶� ���
#include "Components/Image.h" // UImage ����� ���� ���
// #include "Components/SceneCaptureComponent2D.h"
// #include "Engine/TextureRenderTarget2D.h"
// #include "Kismet/GameplayStatics.h"
// #include "UObject/ConstructorHelpers.h"
// #include "CameraForMinimap.h"
// #include "UIManager.h"


UMainUI::UMainUI( const FObjectInitializer& ObjectInitializer ): Super( ObjectInitializer )
{
}

void UMainUI::NativeConstruct()
{
}


void UMainUI::CreateUI()
{
	AddToViewport();
}

/*
void UMainUI::UpdateMiniMap( AActor* cameraActor )
{
	if ( cameraActor == nullptr || m_Material == nullptr)
		return;

	USceneCaptureComponent2D* SceneCaptureComponent = cameraActor->FindComponentByClass< USceneCaptureComponent2D >();
	 
    // ���� Ÿ�����κ��� �̹��� ĸó
    if ( SceneCaptureComponent == nullptr )
        return;

    UTextureRenderTarget2D* RenderTarget = SceneCaptureComponent->TextureTarget;

    if ( RenderTarget == nullptr )
    {
        RenderTarget = NewObject<UTextureRenderTarget2D>();
        RenderTarget->InitAutoFormat( 210, 210 );
        SceneCaptureComponent->TextureTarget = RenderTarget;
    }

    FTextureRenderTargetResource* TextureRenderTargetResource = RenderTarget->GameThread_GetRenderTargetResource();

    if ( TextureRenderTargetResource == nullptr )
        return;

    FReadSurfaceDataFlags ReadSurfaceDataFlags;
    ReadSurfaceDataFlags.SetLinearToGamma( false );

    TArray<FColor> OutBMP;
    TextureRenderTargetResource->ReadPixels( OutBMP, ReadSurfaceDataFlags );

    // ĸó�� �̹����� UTexture2D�� ��ȯ
    UTexture2D* Texture = UTexture2D::CreateTransient( RenderTarget->SizeX, RenderTarget->SizeY, PF_B8G8R8A8 );

    if ( Texture == nullptr )
        return;

    Texture->UpdateResource();
    uint8* MipData = (uint8*)Texture->PlatformData->Mips[ 0 ].BulkData.Lock( LOCK_READ_WRITE );
    FMemory::Memcpy( MipData, OutBMP.GetData(), OutBMP.Num() * sizeof( FColor ) );
    Texture->PlatformData->Mips[ 0 ].BulkData.Unlock();

    // UImage�� �Ҵ�
    UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create( m_Material, GetTransientPackage() );

    if ( MaterialInstance == nullptr )
        return;

    MaterialInstance->SetTextureParameterValue( FName( "Texture" ), Texture );
        
    if ( miniMap_Image != nullptr )
    {
        miniMap_Image->SetBrushFromMaterial( MaterialInstance );
        miniMap_Image->SetBrushSize( FVector2D( RenderTarget->SizeX, RenderTarget->SizeY ) );
    }
}
*/
