// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Type/Enums/GamePlayEnums.h"
#include "MagicBook.generated.h"

class USkeletalMeshComponent;

UCLASS()
class MAGEANDSEEKER_API AMagicBook : public AActor
{
	GENERATED_BODY()
	
public:	
	AMagicBook();
	void BookMatterIntanceUpdatae(EElementalType Type, int32 LV);
	void PlayBookAnim();
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* BookChangeMontage;
};
