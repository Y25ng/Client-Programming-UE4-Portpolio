// Fill out your copyright notice in the Description page of Project Settings.


#include "SeeingThroughActor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"


// Sets default values
ASeeingThroughActor::ASeeingThroughActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASeeingThroughActor::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.SetTickFunctionEnable(false); // 게임이 시작했을 때 Tick 함수를 실행되지 않게 해줌 -> 메모리 낭비X
}

// Called every frame
void ASeeingThroughActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



