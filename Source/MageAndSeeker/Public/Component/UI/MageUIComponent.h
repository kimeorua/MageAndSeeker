// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/UI/PawnUIComponent.h"
#include "Type/MageAndSeekerEnum.h"
#include "MageUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeBook, EBookType, BookType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeMode, bool, IsCombatMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeShowUI, bool, IsShow);

UCLASS()
class MAGEANDSEEKER_API UMageUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnChangeBook OnChangeBook;

	UPROPERTY(BlueprintAssignable)
	FOnChangeMode OnChangeMode;

	UPROPERTY(BlueprintAssignable)
	FOnChangeShowUI OnChangeShowUI;

	UFUNCTION(BlueprintCallable)
	void ChangeBookUI(EBookType BookType);

	UFUNCTION(BlueprintCallable)
	void ChangeCombatMode(bool bIsCombat);
};
