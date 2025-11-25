// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Projectile/BaseProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "MageAndSeekerGameplayTag.h"
#include "Character/MageCharacter.h"

#include "DebugHelper.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SetRootComponent(SphereCollision);
	SphereCollision->SetSphereRadius(90.0f);

	ProjectileFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileFX"));
	ProjectileFX->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	ProjectileMovementComponent->InitialSpeed = 1500.f;
	ProjectileMovementComponent->MaxSpeed = 1500.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
    ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

void ABaseProjectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		FGameplayEventData Data;
		Data.Target = GetOwner();

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), MageAndSeekerGameplayTag::Mage_Event_APCharge, Data);

		FGameplayEventData DamageData;
		DamageData.Target = OtherActor;
		DamageData.Instigator = GetOwner();
		DamageData.TargetTags.AddTag(Cast<AMageCharacter>(GetOwner())->ReturnAttackType());
		// 임시 데미지 //
		DamageData.EventMagnitude = -10000.0f;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OtherActor, MageAndSeekerGameplayTag::Shared_Event_TakeDamage, DamageData);

		Destroy();
	}
}

void ABaseProjectile::InitProjectile(const FVector& ShootDirection, float Speed)
{
	if (ProjectileMovementComponent)
	{
		FVector NormalizedDir = ShootDirection.GetSafeNormal();
		ProjectileMovementComponent->Velocity = NormalizedDir * Speed;

		ProjectileFX->SetVariableFloat(FName("Size"), GetActorScale3D().X);
	}
}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->SetCollisionObjectType(ECC_GameTraceChannel2);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
}