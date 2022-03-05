// Fill out your copyright notice in the Description page of Project Settings.


#include "ABItemBox.h"
#include "Components/BoxComponent.h"
#include "ABCharacter.h"
#include "ABWeapon.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AABItemBox::AABItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);

	Trigger->SetBoxExtent(FVector(40.f, 42.f, 30.f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("StaticMesh'/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'"));
	if (SM_BOX.Succeeded())
	{
		Box->SetStaticMesh(SM_BOX.Object);
	}

	Box->SetRelativeLocation(FVector(0.f, -3.5f, -30.f));

	Box->SetCollisionProfileName(TEXT("NoCollision"));
	Trigger->SetCollisionProfileName(FName(TEXT("ItemBox")));

	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	Effect->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_EFFECT(TEXT("ParticleSystem'/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh'"));
	if (PS_EFFECT.Succeeded())
	{
		Effect->SetTemplate(PS_EFFECT.Object);
		Effect->bAutoActivate = false;
	}

	WeaponItemClass = AABWeapon::StaticClass();
}

// Called when the game starts or when spawned
void AABItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABItemBox::OnCharacterOverlap);

	Effect->OnSystemFinished.AddDynamic(this, &AABItemBox::OnEffectFinished);
}

// Called every frame
void AABItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABItemBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Character = Cast<AABCharacter>(OtherActor);
	if (Character)
	{
		if (Character->CanSetWeapon() && WeaponItemClass != nullptr)
		{
			auto NewWeapon = GetWorld()->SpawnActor<AABWeapon>(
				WeaponItemClass,
				FVector::ZeroVector,
				FRotator::ZeroRotator);
			Character->SetWeapon(NewWeapon);
			Effect->Activate(true);
			Box->SetHiddenInGame(true);
			SetActorEnableCollision(false);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s can't equip Weapon Currently"), *Character->GetName());
		}
	}
}

void AABItemBox::OnEffectFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}

