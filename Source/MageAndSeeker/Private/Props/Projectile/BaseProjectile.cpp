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
		Destroy();
	}
}

void ABaseProjectile::InitProjectile(const FVector& ShootDirection, const FProjectileSpec& Spec)
{
	if (ProjectileMovementComponent)
	{
		FVector NormalizedDir = ShootDirection.GetSafeNormal();
		ProjectileMovementComponent->Velocity = NormalizedDir * Spec.ProjectileSpeed;

		SetActorScale3D(BaseScale * Spec.Size);
		const float VisualSize = BaseScale.X * Spec.Size;

		ProjectileFX->SetVariableFloat(FName("Size"), VisualSize);

		// TODO : 전달받은 Spec을 통해 발송될 GameplayEvent Tag 저장 하기.
	}
}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->SetCollisionObjectType(ECC_GameTraceChannel2);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);

	BaseScale = GetActorScale3D();
}