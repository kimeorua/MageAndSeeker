// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/EnemyWeapon.h"
#include "Components/BoxComponent.h"

AEnemyWeapon::AEnemyWeapon()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxCollision->SetupAttachment(Mesh);
}

void AEnemyWeapon::BeginPlay()
{
	Super::BeginPlay();
}