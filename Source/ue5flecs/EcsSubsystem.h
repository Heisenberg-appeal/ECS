// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "flecs.h"
#include "CoreMinimal.h"
#include "ISMController.h"
#include "Math/UnrealMathUtility.h" 
#include "Subsystems/GameInstanceSubsystem.h"
#include "EcsSubsystem.generated.h"

/**
 *
 */

struct FlecsISMIndex
{
	int Value;
};

struct FlecsISMBeamIndex
{
	int Value;
};
struct FlecsISMRef
{
	AISMController* Value;
};

struct FlecsProjectISMRef
{
	AISMController* Value;
};

struct FlecsBeamCd
{
	int BeamCdTimer;
};

struct FlecsTarget
{
	flecs::entity Target;
	float Distance;
};

struct FlecsBeamTransform
{
	FTransform Value;
};

struct FlecsUnit
{
	FTransform Pos;
	bool IsFriend;
	float Vx;
	float Vy;
	float Vz;
	float SteerTimer;
	bool EnermySpotted;
};

struct FlecsHealth
{
	float Health;
};

struct Enemy {};
struct Units {};
struct Beam {};
struct Friend {};

USTRUCT(BlueprintType)
struct FFlecsEntityHandle
{
	GENERATED_BODY()
	FFlecsEntityHandle() {}
	FFlecsEntityHandle(int InId)
	{
		FlecsEntityId = InId;
	}
	UPROPERTY(BlueprintReadWrite)
	int FlecsEntityId;
};

UCLASS()
class UE5FLECS_API UEcsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	flecs::world* GetEcsWorld() const;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* EnemyRenderer = nullptr;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* FriendRenderer = nullptr;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* BeamRenderer = nullptr;

	AISMController* EnemyISM = nullptr;
	AISMController* FriendISM = nullptr;
	AISMController* BeamRedISM = nullptr;
	AISMController* BeamBlueISM = nullptr;

	 UFUNCTION(BlueprintCallable, Category = "FLECS")
	void InitFlecs(UStaticMesh* InMeshEnemy, UStaticMesh* InMeshFriend, UStaticMesh* InMeshBeamRed, UStaticMesh* InMeshBeamBlue);

	UFUNCTION(BlueprintCallable, Category = "FLECS")
	void SpawnUnitEntity(FVector Location, FRotator Rotation, bool IsFriend, int SpawnNum);
protected:
	FTickerDelegate OnTickDelegate;
	FTSTicker::FDelegateHandle OnTickHandle;
	flecs::world* ECSWorld = nullptr;
	UInstancedStaticMeshComponent* vIsmMap[3] = { nullptr, nullptr, nullptr };
private:
	bool Tick(float DeltaTime);
	void InitIsmRenderers(UStaticMesh* InMeshEnemy, UStaticMesh* InMeshFriend, UStaticMesh* InMeshBeamRed, UStaticMesh* InMeshBeamBlue);

};
