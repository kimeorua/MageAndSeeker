// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Type/Structs/GamePlayStructs.h"
#include "BaseProjectile.generated.h"

class UProjectileMovementComponent;
class UNiagaraComponent;
class USphereComponent;

UCLASS()
class MAGEANDSEEKER_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseProjectile();

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void InitProjectile(const FVector& ShootDirection, const FProjectileSpec& Spec, AActor* OwnerActor);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Movment Component", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FX", meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* ProjectileFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage Type", meta = (AllowPrivateAccess = "true"))
	FGameplayTag DamageTypeTag;

	FVector BaseScale;

	AActor* Owner;

	UPROPERTY()
	FProjectileSpec ChacedSpec;

	void SendPlayerEvent(AActor* Player);

	void SendMonsterEvent_Damage(AActor* Monster, AActor* Player);
};