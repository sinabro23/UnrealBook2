// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Attack.h"
#include "ABCharacter.h"
#include "ABAIController.h"
UMyBTTask_Attack::UMyBTTask_Attack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UMyBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	AABCharacter* Character = Cast<AABCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Character)
		return EBTNodeResult::Failed;
	
		Character->Attack();
		IsAttacking = true;
		Character->OnAttackEnd.AddLambda([this]() -> void {
			IsAttacking = false;
		});

	return EBTNodeResult::InProgress;
}

void UMyBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
