// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/ActivatedProps.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Character/MageCharacter.h"
#include "Components/WidgetComponent.h"

AActivatedProps::AActivatedProps()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(Mesh);

	BoxCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(Mesh);
}

void AActivatedProps::OnBeginOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor) && CastChecked<AMageCharacter>(OtherActor))
	{
		BoxCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);

		WidgetComponent->bHiddenInGame = false;
	}
}

void AActivatedProps::OnEndCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	BoxCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);

	WidgetComponent->bHiddenInGame = true;
}

void AActivatedProps::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndCollision);

	WidgetComponent->bHiddenInGame = true;
}