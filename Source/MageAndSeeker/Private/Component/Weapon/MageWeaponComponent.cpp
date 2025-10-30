// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Weapon/MageWeaponComponent.h"
#include "Props/Weapons/SkeletalWeapon.h"
#include "Props/Weapons/StaticWeapon.h"
#include "Subsystem/SaveLoadSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/EquipmentSubsystem.h"
#include "Props/Module/MagicModule.h"

#include"DebugHelper.h"


#pragma region Basic 함수
void UMageWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UGameplayStatics::GetCurrentLevelName(this, true) == "DevMap")
	{
		SettingAllSaveData();

		CurrentBook = EquipedBooks.FindRef(EBookType::Fire);
	}
}

void UMageWeaponComponent::SettingAllSaveData()
{
	BookSettingInit();
	SettingBookSaveData();
	SettingEquipmentSaveData();
}

void UMageWeaponComponent::SettingBookSaveData()
{
	if (USaveLoadSubsystem* SaveLoadSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<USaveLoadSubsystem>())
	{
		FBookData Data;

		Data = SaveLoadSubsystem->GetLoadedBookData(EBookType::Fire);
		EquipedBooks[EBookType::Fire] = Data;

		Data = SaveLoadSubsystem->GetLoadedBookData(EBookType::Ice);
		EquipedBooks[EBookType::Ice] = Data;

		Data = SaveLoadSubsystem->GetLoadedBookData(EBookType::Lightning);
		EquipedBooks[EBookType::Lightning] = Data;
	}
}

void UMageWeaponComponent::SettingEquipmentSaveData()
{
	if (USaveLoadSubsystem* SaveLoadSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<USaveLoadSubsystem>())
	{
		TMap<int32, FArtifactData> ArtifactLoadedData = SaveLoadSubsystem->GetSavedArtifactInventory();

		if (UEquipmentSubsystem* EquipmentSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UEquipmentSubsystem>())
		{
			RegisterArtifact(EquipmentSubsystem->CreateArtifact(SaveLoadSubsystem->GetEquipedArtifactData().ArtifactID, SaveLoadSubsystem->GetEquipedArtifactData()));

			for (auto& ArtifactData : ArtifactLoadedData)
			{
				{
					EquipmentSubsystem->LoadAndCreateArtifact(ArtifactData.Key, ArtifactData.Value);
				}
			}

			for (FModuleSaveData Data : SaveLoadSubsystem->GetSavedEquipedModule())
			{
				FEquippedMagicModule Module;
				Module.ModuleID = Data.ModuleID;
				Module.ModuleLevel = Data.UpgradeLevel;

				EquipmentSubsystem->CreateModule(Data.Type, Module, GetOwningCharacter_Base());
			}
		}
	}
}

void UMageWeaponComponent::BookSettingInit()
{
	FBookData FireBook, IceBook, LightningBook;
	FireBook.BookLevel = 1;
	FireBook.BookType = EBookType::Fire;
	EquipedBooks.Add(EBookType::Fire, FireBook);

	IceBook.BookLevel = 1;
	IceBook.BookType = EBookType::Ice;
	EquipedBooks.Add(EBookType::Ice, IceBook);

	LightningBook.BookLevel = 1;
	LightningBook.BookType = EBookType::Lightning;
	EquipedBooks.Add(EBookType::Lightning, LightningBook);
}

#pragma endregion

#pragma region 스태프 등록 Mesh 반환

void UMageWeaponComponent::RegisterWeapon(TArray<ABaseWeapon*> WeaponsToRegister)
{
	for (ABaseWeapon* Weapon : WeaponsToRegister)
	{
		if (IsValid(Weapon))
		{
			EquipedWeapons.Add(Weapon->GetWeaponType(), Weapon);
		}
	}
}

AStaticWeapon* UMageWeaponComponent::GetStaff() const
{
	return Cast<AStaticWeapon>(EquipedWeapons.FindRef(EWeaponType::Staff));
}

ASkeletalWeapon* UMageWeaponComponent::GetBook() const
{
	return Cast<ASkeletalWeapon>(EquipedWeapons.FindRef(EWeaponType::Book));
}

#pragma endregion

#pragma region BookFunc
void UMageWeaponComponent::SettingCurrentBook(EBookType BookType)
{
	switch (BookType)
	{
	case EBookType::Fire:
		if (EquipedBooks.Contains(EBookType::Fire))
		{
			CurrentBook = EquipedBooks.FindOrAdd(EBookType::Fire);
		}
		break;
	case EBookType::Ice:
		if (EquipedBooks.Contains(EBookType::Ice))
		{
			CurrentBook = EquipedBooks.FindOrAdd(EBookType::Ice);
		}
		break;
	case EBookType::Lightning:
		if (EquipedBooks.Contains(EBookType::Lightning))
		{
			CurrentBook = EquipedBooks.FindOrAdd(EBookType::Lightning);
		}
		break;
	default:
		break;
	}
}

FBookData UMageWeaponComponent::GetBookData(EBookType BookType)
{
	return EquipedBooks.FindRef(BookType);
}

#pragma endregion

#pragma region 아티팩트

void UMageWeaponComponent::RegisterArtifact(UBaseArtifact* NewArtifact)
{
	if (!NewArtifact) { return; }
	Artifact = NewArtifact;
}

void UMageWeaponComponent::ActivateArtifact()
{
	if (Artifact)
	{
		Artifact->OnActivate();
	}
}
#pragma endregion

#pragma region 모듈
void UMageWeaponComponent::RegisterModule(EBookType Type, UMagicModule* Module)
{
	if (!Modules.Contains(Type))
	{
		Modules.Add(Type, FMagicModules());
	}
	Modules[Type].Modules.Add(Module);
}

void UMageWeaponComponent::ResetModules(EBookType Type)
{
	if (Modules.Contains(Type) && Modules[Type].Modules.Num() > 0)
	{
		if (UEquipmentSubsystem* EquipmentSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UEquipmentSubsystem>())
		{
			for (FEquippedMagicModule Data : GetEquippedModules(Type))
			{
				EquipmentSubsystem->AddModuleToInventory(Type, Data);
			}
		}
		Modules[Type].Modules.Empty();
	}
	else { return; }
}

TArray<FEquippedMagicModule> UMageWeaponComponent::GetEquippedModules(EBookType Type) const
{
	TArray<FEquippedMagicModule> ReturnModules;

	if (Modules.Contains(Type) && Modules[Type].Modules.Num() > 0)
	{
		for (UMagicModule* Module : Modules[Type].Modules)
		{
			FEquippedMagicModule Data;
			Data.ModuleID = Module->GetModuleID();
			Data.ModuleLevel = Module->GetUpgradeLevel();

			ReturnModules.Add(Data);
		}
	}
	return ReturnModules;
}
#pragma endregion

#pragma region 조준선
FVector UMageWeaponComponent::CalculatePosition()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	int32 ViewportX, ViewportY;
	PC->GetViewportSize(ViewportX, ViewportY);

	FVector2D CrosshairScreen(ViewportX * 0.5f, ViewportY * 0.5f);

	FVector WorldLocation, WorldDirection;
	PC->DeprojectScreenPositionToWorld(CrosshairScreen.X, CrosshairScreen.Y, WorldLocation, WorldDirection);

	FVector Start = WorldLocation;
	FVector End = Start + (WorldDirection * 10000.0f);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwningCharacter_Base());

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

	FVector TargetPoint = bHit ? HitResult.Location : End;

	return TargetPoint;
}
#pragma endregion