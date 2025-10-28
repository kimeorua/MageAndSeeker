// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MageCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAsset/DataAsset_InputConfig.h"
#include "Component/MageAndSeekerInputComponent.h"
#include "MageAndSeekerGameplayTag.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Props/ActivatedProps.h"
#include "GAS/AttributeSet/MageAttributeSet.h"
#include "GAS/AttributeSet/ArtifactAttributeSet.h"
#include "Component/UI/MageUIComponent.h"
#include "UI/MageAndSeekerWidget.h"
#include "Component/Weapon/MageWeaponComponent.h"


#include "DebugHelper.h"

#pragma region Basic
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

	MASInputComponent->BindNativeInputAction(DataAsset_InputConfig, MageAndSeekerGameplayTag::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	MASInputComponent->BindNativeInputAction(DataAsset_InputConfig, MageAndSeekerGameplayTag::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	MASInputComponent->BindNativeInputAction(DataAsset_InputConfig, MageAndSeekerGameplayTag::InputTag_Interection, ETriggerEvent::Started, this, &ThisClass::Input_Interactive);

	MASInputComponent->BindAbilityInputAction(DataAsset_InputConfig, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputRelased);
}
#pragma endregion

#pragma region Input
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

void AMageCharacter::Input_Interactive()
{
	FHitResult HitResult;
	FVector Start = GetActorLocation();
	FVector End = Start;

	float Radius = 300.0f;

	ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Cast<AActor>(this));

	FHitResult Hit;

	ActivatedProp = nullptr;

	bool bHit = UKismetSystemLibrary::SphereTraceSingle
	(
		this, 
		Start, 
		End, 
		Radius, 
		TraceType,
		false,
		ActorsToIgnore,
		bIsTraceShow ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		Hit,
		true
	);

	if (bHit && Hit.GetActor())
	{
		ActivatedProp = Cast<AActivatedProps>(Hit.GetActor());
		ActivatedProp->ActivateProp();

		GetMageUIComponent()->OnChangeShowUI.Broadcast(false);
	}
}

void AMageCharacter::EndInteractive()
{
	if (IsValid(ActivatedProp))
	{
		GetMageUIComponent()->OnChangeShowUI.Broadcast(true);
		ActivatedProp->DeactivateProp();
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
#pragma endregion

#pragma region DIP
UPawnUIComponent* AMageCharacter::GetPawnUIComponent() const
{
	return MageUIComponent;
}

UMageUIComponent* AMageCharacter::GetMageUIComponent() const
{
	return MageUIComponent;
}

UPawnWeaponComponent* AMageCharacter::GetPawnWeaponComponent() const
{
	return MageWeaponComponent;
}

UMageWeaponComponent* AMageCharacter::GetMageWeaponComponent() const
{
	return MageWeaponComponent;
}

void AMageCharacter::CreateUIAndAdd()
{
	APlayerController* PC = Cast<APlayerController>(GetController());

	if (HUDWidgetClass)
	{
		UUserWidget* HUD = CreateWidget<UUserWidget>(PC, HUDWidgetClass);

		if (HUD) { HUD->AddToViewport(); }
	}
}
#pragma endregion

#pragma region privateFunc
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

	MageUIComponent = CreateDefaultSubobject<UMageUIComponent>(TEXT("Mage UI Component"));
	MageWeaponComponent = CreateDefaultSubobject<UMageWeaponComponent>(TEXT("Mage Weapon Component"));
}
#pragma endregion