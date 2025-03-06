// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FriendActor.h"
#include "BeamActor.h"
#include "ISMController.h"
#include "ActorSubsystem.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FActorPair
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Actor Pair")
	AFriendActor* UnitActor;

	UPROPERTY(BlueprintReadWrite, Category = "Actor Pair")
	ABeamActor* BeamActor;
};

UCLASS()
class UE5FLECS_API UActorSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection);

	UFUNCTION(BlueprintCallable, Category = "ActorCompare")
	void SpawnUnitEntity(FVector Location, FRotator Rotation, bool IsFriend, int SpawnNum);

	UFUNCTION(BlueprintCallable, Category = "ActorCompare")
	void UpdateBeam(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "ActorCompare")
	void InitActorSystem(UStaticMesh* InMeshEnemy, UStaticMesh* InMeshFriend, UStaticMesh* InMeshBeamRed, UStaticMesh* InMeshBeamBlue);

public:

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* EnemyRenderer = nullptr;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* FriendRenderer = nullptr;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* BeamRenderer = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMesh* mInMeshEnemy = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMesh* mInMeshFriend = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMesh* mInMeshBeam = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMesh* mInMeshBeamBlue = nullptr;


	TArray<FActorPair> ActorPairs;

private:

	TSubclassOf<AFriendActor> MyFriendClass;

};