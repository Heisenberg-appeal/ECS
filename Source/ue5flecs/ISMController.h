// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "ISMController.generated.h"

UCLASS()
class UE5FLECS_API AISMController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AISMController();

	//ISM API functions
	void Initialize(UStaticMesh* InMesh) const;

	int32 GetInstanceCount() const;

	void CreateOrExpandTransformArray();

	int32 AddInstance(FTransform Transform);

	int32 AddInstance();

	void SetTransform(int32 InstanceIndex, const FTransform& Transform);

	void RemoveInstance(int32 InstanceIndex);

	void BatchUpdateTransform() const;

	void UpdateInstanceTransform(int32 InstanceIndex, FTransform& Transform);

	bool CheckIndexPool();

public:
	//Component fields
	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* InstancedStaticMeshComponent = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	TArray<FTransform> Transforms;
	TQueue<int> IndexPool;

};
