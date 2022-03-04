// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimInstance.h"
#include "ABCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UABAnimInstance::UABAnimInstance()
{
	CurrentPawnSpeed = 0.f;
	bIsInAir = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("AnimMontage'/Game/_Game/Animations/SK_Mannequin_Skeleton_Montage.SK_Mannequin_Skeleton_Montage'"));
	

	if(ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	//Super::NativeUpdateAnimation(DeltaSeconds);
	//AABCharacter* Character = Cast<AABCharacter>(TryGetPawnOwner());
	//if (Character)
	//{
	//	CurrentPawnSpeed = Character->GetVelocity().Size();
	//}

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<AABCharacter>(Pawn);
		if (Character)
		{
			bIsInAir = Character->GetCharacterMovement()->IsFalling();
		}
	}
}

void UABAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage, 1.f);
}

void UABAnimInstance::JumpToSection(int32 MontageSection)
{
	FName Name = GetAttackMontageName(MontageSection);
	Montage_JumpToSection(Name, AttackMontage);
}

FName UABAnimInstance::GetAttackMontageName(int32 MontageSection)
{
	return FName(*FString::Printf(TEXT("Attack%d"), MontageSection));
}


void UABAnimInstance::AnimNotify_AttackHitCheck()
{
	UE_LOG(LogTemp, Warning, TEXT("AttackHit"));
	OnAttackHitCheck.Broadcast(); // 이때 어택 히트를 체크하라고 알려주는것
}
