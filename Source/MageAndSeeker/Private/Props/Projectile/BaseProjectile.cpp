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
	if (IsValid(OtherActor) && IsValid(Owner))
	{
		SendPlayerEvent(Owner);
		SendMonsterEvent_Damage(OtherActor, Owner);

		Destroy();
	}
}

void ABaseProjectile::InitProjectile(const FVector& ShootDirection, const FProjectileSpec& Spec, AActor* OwnerActor)
{
	ChacedSpec = FProjectileSpec();

	if (ProjectileMovementComponent)
	{
		FVector NormalizedDir = ShootDirection.GetSafeNormal();
		ProjectileMovementComponent->Velocity = NormalizedDir * Spec.ProjectileSpeed;

		SetActorScale3D(BaseScale * Spec.Size);
		const float VisualSize = BaseScale.X * Spec.Size;

		ProjectileFX->SetVariableFloat(FName("Size"), VisualSize);

		ChacedSpec = Spec;

		Owner = OwnerActor;
	}
}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->SetCollisionObjectType(ECC_GameTraceChannel2);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);

	BaseScale = GetActorScale3D();
}

void ABaseProjectile::SendPlayerEvent(AActor* Player)
{
	FGameplayEventData PlayerEventData;
	PlayerEventData.Instigator = Player;
	PlayerEventData.Target = Player;
	PlayerEventData.EventMagnitude = ChacedSpec.APChargeRate;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Player, MageAndSeekerGameplayTag::Mage_Event_APCharge, PlayerEventData);
}

void ABaseProjectile::SendMonsterEvent_Damage(AActor* Monster, AActor* Player)
{
	FGameplayEventData MonsterEventData;
	MonsterEventData.Instigator = Player;
	MonsterEventData.InstigatorTags.AddTag(DamageTypeTag);
	MonsterEventData.Target = Monster;
	MonsterEventData.EventMagnitude = ChacedSpec.DamageRate;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Player, MageAndSeekerGameplayTag::Shared_Event_TakeDamage, MonsterEventData);
}

void ABaseProjectile::SendMonsterEvent_RuneEffect(AActor* Monster, AActor* Player)
{
	FGameplayEventData RuneEffectData;
	RuneEffectData.Instigator = Player;
	RuneEffectData.Target = Monster;
	//RuneEffectData.EventTag = ChacedSpec.SendToMonsterEventTags;
}
