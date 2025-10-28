// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/UI/PawnUIComponent.h"
#include "Type/MageAndSeekerEnum.h"
#include "MageUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeBook, EBookType, BookType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeMode, bool, IsCombatMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeShowUI, bool, IsShow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSettingMaxMana, float, MaxMP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeCurrentMP, float, Percent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeCurrentAP, float, Percent);

UCLASS()
class MAGEANDSEEKER_API UMageUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()
	
public:
#pragma region Delegate
	UPROPERTY(BlueprintAssignable)
	FOnChangeBook OnChangeBook;

	UPROPERTY(BlueprintAssignable)
	FOnChangeMode OnChangeMode;

	UPROPERTY(BlueprintAssignable)
	FOnChangeShowUI OnChangeShowUI;

	UPROPERTY(BlueprintAssignable)
	FOnSettingMaxMana OnSettingMaxMana;

	UPROPERTY(BlueprintAssignable)
	FOnChangeCurrentMP OnChangeCurrentMP;

	UPROPERTY(BlueprintAssignable)
	FOnChangeCurrentAP OnChangeCurrentAP;
#pragma endregion

#pragma region Delegate_Call_Func
	UFUNCTION(BlueprintCallable)
	void ChangeBookUI(EBookType BookType);

	UFUNCTION(BlueprintCallable)
	void ChangeCombatMode(bool bIsCombat);
#pragma endregion
};
