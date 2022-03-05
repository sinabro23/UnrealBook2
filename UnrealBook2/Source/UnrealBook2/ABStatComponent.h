// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ABStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZero)
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALBOOK2_API UABStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UABStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
	
public:
	void SetNewLevel(int32 NewLevel); // 이 함수를 통해서만 스탯변화를 가져올 수 있게.(레벨업)
	float GetAttack();
	void SetDamage(float NewDamage);

private:
	struct FABCharacterData* CurrentStatData = nullptr;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentHP;

public:
	FOnHPIsZero OnHPIsZero;
};
