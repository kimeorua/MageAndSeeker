// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnExtensionComponent.h"
#include "PawnUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangedHP, float, Percent, float, MaxHP);

UCLASS()
class MAGEANDSEEKER_API UPawnUIComponent : public UPawnExtensionComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnChangedHP OnChangedHP;
};
