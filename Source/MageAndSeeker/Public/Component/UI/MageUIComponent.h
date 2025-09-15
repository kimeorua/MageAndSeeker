// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/UI/PawnUIComponent.h"
#include "Type/MageAndSeekerEnum.h"
#include "MageUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeBook, EBookType, BookType);

UCLASS()
class MAGEANDSEEKER_API UMageUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnChangeBook OnChangeBook;

	UFUNCTION(BlueprintCallable)
	void ChangeBookUI(EBookType BookType);
};
