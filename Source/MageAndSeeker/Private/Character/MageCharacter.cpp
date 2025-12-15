// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MageCharacter.h"
//------------------------ Component ------------------------//
#include "GameFramework/SpringArmComponent.h"
#include "Component/Combat/MageCombatComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/MageAndSeekerInputComponent.h"
#include "Component/Rune/MageRuneComponent.h"
#include "Component/UI/MageUIComponent.h"
#include "Component/StatSave/MageStatSaveComponent.h"
//------------------------ Component ------------------------//

//------------------------ AttributeSet ------------------------//
#include "GAS/AttributeSet/MageAttributeSet.h"
#include "GAS/AttributeSet/ArtifactAttributeSet.h"
//------------------------ AttributeSet ------------------------//

//------------------------ DataAsset ------------------------//
#include "DataAsset/DataAsset_InputConfig.h"
#include "DataAsset/StartUp/DataAsset_StartUp.h"
//------------------------ DataAsset ------------------------//

//------------------------ Subsystem ------------------------//
#include "EnhancedInputSubsystems.h"
#include "Subsystem/SaveLoadSubsystem.h"
//------------------------ Subsystem ------------------------//

//------------------------ etc ------------------------//
#include "MageAndSeekerGameplayTag.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Props/ActivatedProps.h"
//------------------------ etc ------------------------//

AMageCharacter::AMageCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	MageInit();
}

void AMageCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMageCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AMageCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(DataAsset_InputConfig, TEXT("Forgot to Assign a DataAsset_InputConfig"));
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(DataAsset_InputConfig->InputMappingContext, 0);
	UMageAndSeekerInputComponent* MASInputComponent = CastChecked<UMageAndSeekerInputComponent>(PlayerInputComponent);

	MASInputComponent->BindNativeInputAction(DataAsset_InputConfig, MageAndSeekerGameplayTag::InputTag_Move, ETriggerEvent::Triggered, this, &AMageCharacter::Input_Move);
	MASInputComponent->BindNativeInputAction(DataAsset_InputConfig, MageAndSeekerGameplayTag::InputTag_Look, ETriggerEvent::Triggered, this, &AMageCharacter::Input_Look);

	MASInputComponent->BindAbilityInputAction(DataAsset_InputConfig, this, &AMageCharacter::Input_AbilityInputPressed, &AMageCharacter::Input_AbilityInputRelased);
}

void AMageCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

	if (MovementVector.Y != 0.0f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.0f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMageCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.0f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.0f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMageCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	MASAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AMageCharacter::Input_AbilityInputRelased(FGameplayTag InInputTag)
{
	MASAbilitySystemComponent->OnAbilityInputRelased(InInputTag);
}

void AMageCharacter::MageInit()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 20.0f, 80.0f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	MageAttributeSet = CreateDefaultSubobject<UMageAttributeSet>(TEXT("MageAttributeSet"));
	ArtifactAttributeSet = CreateDefaultSubobject<UArtifactAttributeSet>(TEXT("ArtifactAttributeSet"));

	MageCombatComponent = CreateDefaultSubobject<UMageCombatComponent>(TEXT("MageCombatComponent"));
	MageRuneComponent = CreateDefaultSubobject<UMageRuneComponent>(TEXT("MageRuneComponent"));
	MageUIComponent = CreateDefaultSubobject<UMageUIComponent>(TEXT("MageUIComponent"));
	MageStatSaveComponent = CreateDefaultSubobject<UMageStatSaveComponent>(TEXT("MageStatSaveComponent"));
}

void AMageCharacter::InitCharacterStatAndAbility()
{
	MageUIComponent->InitCharacterUI(this);

	USaveLoadSubsystem* SaveSubsystem = GetGameInstance()->GetSubsystem<USaveLoadSubsystem>();

	if (SaveSubsystem)
	{
		SaveSubsystem->LoadGameAsync(SaveSubsystem->GetSlotIndex(), this);
	}

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUp* LodedData = CharacterStartUpData.LoadSynchronous())
		{
			int32 AbilityApplyLevel = 1;
			LodedData->GiveToAbilitySystemComponent(MASAbilitySystemComponent, AbilityApplyLevel);
		}
	}
}