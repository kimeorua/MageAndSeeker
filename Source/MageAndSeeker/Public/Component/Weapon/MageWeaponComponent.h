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

#pragma region Value

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mage Weapon", meta = (AllowPrivateAccess = "true"))
	TMap<EWeaponType, ABaseWeapon*>EquipedWeapons;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mage Weapon", meta = (AllowPrivateAccess = "true"))
	TMap<EBookType, FBookData>EquipedBooks;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mage Weapon", meta = (AllowPrivateAccess = "true"))
	FBookData CurrentBook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Artifacte", meta = (AllowPrivateAccess = "true"))
	UBaseArtifact* Artifact = nullptr;

	UPROPERTY(VisibleAnywhere)
	TMap<EBookType, FMagicModules>Modules;

#pragma endregion

protected:

#pragma region Basic

	virtual void BeginPlay() override;

	void SettingAllSaveData();
	void SettingBookSaveData();
	void SettingEquipmentSaveData();
	void BookSettingInit();

#pragma endregion

public:

#pragma region 스태프 등록 Mesh 반환
	virtual void RegisterWeapon(TArray<ABaseWeapon*> WeaponsToRegister) override;

	UFUNCTION(BlueprintPure)
	AStaticWeapon* GetStaff() const;

	UFUNCTION(BlueprintPure)
	ASkeletalWeapon* GetBook() const;

#pragma endregion

#pragma region 모듈 관련 함수

	void RegisterModule(EBookType Type, UMagicModule* Module);

	void ResetModules(EBookType Type);

	TArray<FEquippedMagicModule> GetEquippedModules(EBookType Type) const;
	
#pragma endregion

#pragma region Book

	UFUNCTION(BlueprintCallable)
	void SettingCurrentBook(EBookType BookType);

	FBookData GetBookData(EBookType BookType);

#pragma endregion

#pragma region 아티팩트 관련 함수

	UFUNCTION(BlueprintCallable)
	void RegisterArtifact(UBaseArtifact* NewArtifact);

	UFUNCTION(BlueprintCallable)
	void ActivateArtifact();

	UFUNCTION(BlueprintPure)
	FORCEINLINE UBaseArtifact* GetArtifact() { return Artifact; }

#pragma endregion

#pragma region 조준선 관련 함수
	UFUNCTION(BlueprintPure)
	FVector CalculatePosition();
#pragma endregion
};