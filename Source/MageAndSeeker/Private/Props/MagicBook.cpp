// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/MagicBook.h"
#include "Components/SkeletalMeshComponent.h"

static const float BrightnessTable[] = { 1.f, 5.f, 10.f, 20.f };
static const float MetalricTable[] = { 0.2f, 0.3f, 0.5f, 1.f };

AMagicBook::AMagicBook()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}
void AMagicBook::BookMatterIntanceUpdatae(EElementalType Type, int32 LV)
{
	UMaterialInstanceDynamic* DynMat = Mesh->CreateDynamicMaterialInstance(0);

    if (!DynMat) return;

    FLinearColor Color;

    switch (Type)
    {
    case EElementalType::Fire:
        Color = FLinearColor(1.f, 0.14f, 0.f);
        break;

    case EElementalType::Ice:
        Color = FLinearColor(0.0f, 0.27f, 1.f);
        break;

    case EElementalType::Lightning:
        Color = FLinearColor(1.0f, 0.92f, 0.f);
        break;

    default:
        Color = FLinearColor::White;
        break;
    }

    float Brightness = BrightnessTable[FMath::Clamp(LV - 1, 0, 3)];
    float Metalric = MetalricTable[FMath::Clamp(LV - 1, 0, 3)];
      
    DynMat->SetVectorParameterValue(TEXT("Color"), Color);
    DynMat->SetScalarParameterValue(TEXT("Brightness"), Brightness);
    DynMat->SetScalarParameterValue(TEXT("Metalric"), Metalric);
}

void AMagicBook::PlayBookAnim()
{
    Mesh->PlayAnimation(BookChangeMontage, false);
}

void AMagicBook::BeginPlay()
{
	Super::BeginPlay();
}

