// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MageAndSeekerWidget.generated.h"

class UMageUIComponent;

UCLASS()
class MAGEANDSEEKER_API UMageAndSeekerWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Mage UIComponent Initalized"))
	void BP_OnOwningMageUIComponentInitalized(UMageUIComponent* OwingHeroUIComponent);
};
