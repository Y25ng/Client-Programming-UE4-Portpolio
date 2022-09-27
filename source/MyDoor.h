// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"// box �浹ü�� ���� ���̺귯��
#include "MyDoor.generated.h"

UCLASS()
class MYPROJECT2_API AMyDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//UStaticMeshComponent* DoorMesh; // �� Mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* CollisionBox; // �浹ü

	UPROPERTY(EditAnywhere)
		float CloseTime; // ���� �����µ��� �ɸ��� �ð�

	float DoorDeltaTime; // ���� ���� �ݴµ��� ����� �ð� ����

	bool bOpen; // ���� �����ִ����� ���� ���θ� �Ҵ�
	bool bOnlyBoss; // ���� ���� ���͵��� ��� �׿������� ���� ���θ� �Ҵ� 

	FTimerHandle DoorTimerHandle; // �� ���� �ݴ� �ð��� üũ�� �� ����� Ÿ�̸�

	FRotator OriginRotation; // ���� ���� ������ ȸ����

	void Open(); // �� ���� �Լ�

	float StartAngle;
	float EndAngle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		class USoundCue* DoorOpen_Sound; // ����Ʈ ���� ����
};
