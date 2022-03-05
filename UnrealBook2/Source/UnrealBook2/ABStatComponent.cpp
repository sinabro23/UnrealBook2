// Fill out your copyright notice in the Description page of Project Settings.


#include "ABStatComponent.h"
#include "ABGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UABStatComponent::UABStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
	// ...
}


// Called when the game starts
void UABStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UABStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level); // 레벨 초기값 1
}

void UABStatComponent::SetNewLevel(int32 NewLevel)
{
	auto GameInstance = Cast<UABGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		CurrentStatData = GameInstance->GetABCharacterData(Level);
		if (CurrentStatData)
		{
			Level = NewLevel;
			CurrentHP = CurrentStatData->MaxHp; // 렙업하면 만피
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Level %d data doesn't exist"), NewLevel);
		}

	}
}

float UABStatComponent::GetAttack()
{
	if (!CurrentStatData)
		return 0;
	return CurrentStatData->Attack;
}

void UABStatComponent::SetDamage(float NewDamage)
{
	if (!CurrentStatData)
		return;

	CurrentHP = FMath::Clamp(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHp);
	if (CurrentHP <= 0.f)
	{
		OnHPIsZero.Broadcast();
	}
}



