// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionTypes.h"
#include "Engine/DataTable.h" // ���������̺� ��� ���̺귯��
#include "MyBasicCharacter.h"
#include "MyNPCbot.generated.h"

USTRUCT(BlueprintType) // ����ü �������Ʈ ����
struct FShop : public FTableRowBase // ���� ������ ����
{
	GENERATED_BODY()
public:
	FShop()
	{
		ItemNumber = 0;
		ItemPrice = 0;
		ItemName = "";
		ItemExplanation = "";
		ItemIcon = nullptr;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemPrice;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemExplanation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* ItemIcon;
};

UCLASS()
class MYPROJECT2_API AMyNPCbot : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyNPCbot();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USphereComponent* CollisionSphere;

	bool isTalk;

	virtual void FaceRotation(FRotator NewRotation, float DeltaTime = 0.f)override;

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* BotBehavior;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
		class USoundCue* InteractSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDataTable* MyShopDataTable; // ������ ���� ������ ���̺�
	FShop* MyCurrentShopItem; // ������ ���� ������ ���̺� ��� ����ü ������ ��ü

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsShowShop;

	void OpenShop();
	void CloseShop();

	void BuyItem1(int32 Cnt);
	void BuyItem2(int32 Cnt);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		class USoundCue* StoreSound; // ���� ���� ����


private:
	TSubclassOf<class UUserWidget>uiShopBPClass;
	UUserWidget* uiShopWidget;

	class AMyBasicCharacter* PlayerCharac; // �÷��̾�
};
