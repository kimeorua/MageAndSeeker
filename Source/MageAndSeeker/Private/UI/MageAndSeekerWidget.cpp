// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MageAndSeekerWidget.h"
#include "Interface/PawnUIInterface.h"

void UMageAndSeekerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UMageUIComponent* MageUIComponent = PawnUIInterface->GetMageUIComponent())
		{
			BP_OnOwningMageUIComponentInitalized(MageUIComponent);
		}
	}
}