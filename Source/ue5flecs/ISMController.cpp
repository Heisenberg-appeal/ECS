// Fill out your copyright notice in the Description page of Project Settings.


#include "ISMController.h"

// Sets default values
AISMController::AISMController()
{
	PrimaryActorTick.bCanEverTick = false;

	InstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
	SetRootComponent(InstancedStaticMeshComponent);

}

void AISMController::Initialize(UStaticMesh* InMesh) const
{
	InstancedStaticMeshComponent->SetStaticMesh(InMesh);
	InstancedStaticMeshComponent->CastShadow = true;
	InstancedStaticMeshComponent->bCastDynamicShadow = true;
	InstancedStaticMeshComponent->bCastStaticShadow = true;
	InstancedStaticMeshComponent->bUseDefaultCollision = false;
	InstancedStaticMeshComponent->SetGenerateOverlapEvents(false);
	InstancedStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	InstancedStaticMeshComponent->SetCanEverAffectNavigation(false);

	InstancedStaticMeshComponent->NumCustomDataFloats = 1;
}
int32 AISMController::GetInstanceCount() const
{
	return InstancedStaticMeshComponent->GetInstanceCount();
}



int32 AISMController::AddInstance(FTransform transform)
{
	int32 instanceIndex;
	if (IndexPool.IsEmpty())
	{
		instanceIndex = InstancedStaticMeshComponent->AddInstance(transform);
	}
	else
	{
		//indexPool.Dequeue(instanceIndex);
		//InstancedStaticMeshComponent->SetCustomDataValue(instanceIndex, 0, 0);
		instanceIndex = InstancedStaticMeshComponent->AddInstance(transform);
		//InstancedStaticMeshComponent->UpdateInstanceTransform(instanceIndex, transform);
	}
	return instanceIndex;
}


bool AISMController::CheckIndexPool()
{
	if (IndexPool.IsEmpty())
		return true;
	else
		return false;
}
int32 AISMController::AddInstance()
{
	return AddInstance(FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector::ZeroVector));
}

void AISMController::RemoveInstance(int32 instanceIndex)
{
	//indexPool.Enqueue(instanceIndex);

	//Just hide an instance without actual removing
	//Soon newly added instance replace the hidden one
	InstancedStaticMeshComponent->UpdateInstanceTransform(instanceIndex, FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector(0, 1, 1)));
	//InstancedStaticMeshComponent->SetCustomDataValue(instanceIndex, 0, 1);
}

void AISMController::CreateOrExpandTransformArray()
{
	if (GetInstanceCount() != Transforms.Num())
	{
		Transforms.AddUninitialized(GetInstanceCount() - Transforms.Num());
		for (auto i = 0; i < Transforms.Num(); i++)
		{
			Transforms[i] = FTransform{ FVector::ZeroVector };
		}
	}
}

void AISMController::SetTransform(int32 instanceIndex, const FTransform& transform)
{
	Transforms[instanceIndex] = transform;
}


void AISMController::BatchUpdateTransform() const
{
	if (Transforms.Num() > 0)
	{
		InstancedStaticMeshComponent->BatchUpdateInstancesTransforms(0, Transforms, true, true);
	}
}

void AISMController::UpdateInstanceTransform(int32 instanceIndex, FTransform& transform)
{
	InstancedStaticMeshComponent->UpdateInstanceTransform(instanceIndex, transform);
}

// Called when the game starts or when spawned
void AISMController::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AISMController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
