// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponent.generated.h"

class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGEANDSEEKER_API UPawnExtensionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	template<class T>
	T* GetOwningAs() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AActor>::Value, "T Template Parmeter get  GetPawn must be derived form APawn");
		return CastChecked<T>(GetOwner());
	}
	ABaseCharacter* GetOwningCharacter_Base() const
	{
		return this->GetOwningAs<ABaseCharacter>();
	}
};
