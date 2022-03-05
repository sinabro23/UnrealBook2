// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ABCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	PREINIT,
	LOADING,
	READY,
	DEAD
};

enum class EControlMode
{
	GTA,
	DIABLO,
	NPC
};

DECLARE_MULTICAST_DELEGATE(FOnAttackEndedDelegate);

UCLASS()
class UNREALBOOK2_API AABCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacter();
	void SetCharacterState(ECharacterState NewState);
	ECharacterState GetCharacterState() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void SetControlMode(EControlMode ControlMode); // 인칭 변환을 위함
	EControlMode CurrentControlMode = EControlMode::GTA;
	FVector DirectionToMove = FVector::ZeroVector;

	float ArmLengthTo = 0.f;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.f;
	float ArmRotationSpeed = 0.f;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController)override;
public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
	bool bIsAttacking;

	UPROPERTY()
	int32 AttackSectionIndex = 0;

	UPROPERTY()
	class UABAnimInstance* ABAnim;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, Category = Waepon)
	class AABWeapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UABStatComponent* CharacterStat;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;
public:
	void UpDown(float Value);
	void LeftRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	void ViewChange();

	void Attack();

	UFUNCTION()
	void AttackHitCheck(); //애님노티파이에서 타이밍 알려줌

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted); 

	bool CanSetWeapon();

	void SetWeapon(class AABWeapon* NewWeapon);
	
private:

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	float AttackRange;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	float AttackRadius;

	void OnAssetLoadCompleted();

	int32 AssetIndex = 0;
private:

	FSoftObjectPath CharacterAssetToLoad = FSoftObjectPath(nullptr);
	TSharedPtr<struct FStreamableHandle> AssetStreamingHandle;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
	ECharacterState CurrentState;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
	bool bIsPlayer;

	UPROPERTY()
	class AABAIController* ABAIController;

	UPROPERTY()
	class AABPlayerController* ABPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, Meta = (AllowPrivateAccess = true))
	float DeadTimer;

	FTimerHandle DeadTimerHandle = {};

public:
	FOnAttackEndedDelegate OnAttackEnd;
};
