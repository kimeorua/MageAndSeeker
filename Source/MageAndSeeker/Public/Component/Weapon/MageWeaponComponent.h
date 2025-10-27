// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Weapon/PawnWeaponComponent.h"
#include "Type/MageAndSeekerEnum.h"
#include "Type/MageAndSeekerStruct.h"
#include "MageWeaponComponent.generated.h"

class ABaseWeapon;
class ASkeletalWeapon;
class AStaticWeapon;
class UBaseArtifact;
class UMagicModule;

UCLASS()
class MAGEANDSEEKER_API UMageWeaponComponent : public UPawnWeaponComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mage Weapon", meta = (AllowPrivateAccess = "true"))
	TMap<EWeaponType, ABaseWeapon*>EquipedWeapons;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mage Weapon", meta = (AllowPrivateAccess = "true"))
	TMap<EBookType, FBookData>EquipedBooks;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mage Weapon", meta = (AllowPrivateAccess = "true"))
	FBookData CurrentBook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Artifacte", meta = (AllowPrivateAccess = "true"))
	UBaseArtifact* Artifact = nullptr;

protected:
	virtual void BeginPlay() override;

public:
	virtual void RegisterWeapon(TArray<ABaseWeapon*> WeaponsToRegister) override;
	
	UFUNCTION(BlueprintPure)
	AStaticWeapon* GetStaff() const;

	UFUNCTION(BlueprintPure)
	ASkeletalWeapon* GetBook() const;

	UFUNCTION(BlueprintCallable)
	void SettingCurrentBook(EBookType BookType);

	UFUNCTION(BlueprintPure)
	FVector CalculatePosition();

	FBookData GetBookData(EBookType BookType);

	UFUNCTION(BlueprintCallable)
	void RegisterArtifact(UBaseArtifact* NewArtifact);

	UFUNCTION(BlueprintCallable)
	void ActivateArtifact();

	UFUNCTION(BlueprintPure)
	FORCEINLINE UBaseArtifact* GetArtifact() { return Artifact; }
};