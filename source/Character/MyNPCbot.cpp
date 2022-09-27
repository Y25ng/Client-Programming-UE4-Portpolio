// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNPCbot.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "AController_StartMenu.h"
#include "Components/SceneComponent.h"
#include "Engine.h"
#include "MyBasicCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "UI_Shop_Widget.h"
#include "UI_Inventory_Widget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyNPCbot::AMyNPCbot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("GateCollisionSphere"));
	CollisionSphere->SetupAttachment(this->GetCapsuleComponent());
	CollisionSphere->InitSphereRadius(250.0f);

	isTalk = false;
	bIsShowShop = false;

	MyShopDataTable = CreateDefaultSubobject<UDataTable>(TEXT("MyShopDataTable")); // 상점 아이템 정보 데이터 테이블의 기반 구조체 객체 생성
	static ConstructorHelpers::FObjectFinder<UDataTable> MyShop_Obj(TEXT("/Game/Data/MyShop_DataTable"));
	if (MyShop_Obj.Succeeded())
	{
		MyShopDataTable = MyShop_Obj.Object;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> ShopUI(TEXT("/Game/Blueprints/UI/BP_Shop"));
	if (ShopUI.Succeeded())
	{
		uiShopBPClass = ShopUI.Class;
	}

}

// Called when the game starts or when spawned
void AMyNPCbot::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMyNPCbot::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AMyNPCbot::OnOverlapEnd);
}

// Called every frame
void AMyNPCbot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector PlayerPos = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
	FVector myLoc = GetActorLocation();

	FVector Forward = (PlayerPos - myLoc);
	FRotator PlayerRot = FRotationMatrix::MakeFromX(Forward).Rotator();

	if (isTalk)
	{
		FaceRotation(PlayerRot, 0.01f);
	}
}



// Called to bind functionality to input
void AMyNPCbot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyNPCbot::FaceRotation(FRotator NewRotation, float DeltaTime)
{
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.0f);
	Super::FaceRotation(CurrentRotation, DeltaTime);
}

void AMyNPCbot::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor && (OtherActor->IsA(AMyBasicCharacter::StaticClass()) && !isTalk))
	{
		PlayerCharac = Cast<AMyBasicCharacter>(OtherActor);
		UGameplayStatics::PlaySound2D(this, InteractSound);
		isTalk = true;

		OpenShop();

		AAController_StartMenu* contoller = Cast<AAController_StartMenu>(GetWorld()->GetFirstPlayerController());
		contoller->ShowInventory();

		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;
		GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = true;
	}
}

void AMyNPCbot::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor->IsA(AMyBasicCharacter::StaticClass()) && isTalk))
	{
		isTalk = false;

		CloseShop();

		AAController_StartMenu* contoller = Cast<AAController_StartMenu>(GetWorld()->GetFirstPlayerController());
		contoller->CloseInventory();

		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		GetWorld()->GetFirstPlayerController()->bEnableClickEvents = false;
		GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = false;
	}
}

void AMyNPCbot::OpenShop()
{
	if (uiShopBPClass && bIsShowShop == false)
	{
		uiShopWidget = CreateWidget<UUserWidget>(GetWorld(), uiShopBPClass);
		if (uiShopWidget)
		{
			(Cast<UUI_Shop_Widget>(uiShopWidget))->NPCBot = this;
			uiShopWidget->AddToViewport();
		}
		bIsShowShop = true;

		if(StoreSound) // 상점 오픈 소리 출력
			UGameplayStatics::SpawnSoundAttached(StoreSound, RootComponent, NAME_None, FVector::ZeroVector, EAttachLocation::SnapToTarget, true);
	}
}

void AMyNPCbot::CloseShop()
{
	uiShopWidget->RemoveFromViewport();
	bIsShowShop = false;
}

void AMyNPCbot::BuyItem1(int32 Cnt)
{
	PlayerCharac->MyCurrentItem = PlayerCharac->MyItemDataTable->FindRow<FItem>(*FString::FromInt(1), TEXT(""));
	int32 CurrentCnt = PlayerCharac->MyCurrentItem->ItemCnt;

	MyCurrentShopItem = MyShopDataTable->FindRow<FShop>(*FString::FromInt(1), TEXT(""));
	
	if ((MyCurrentShopItem->ItemPrice) * Cnt <= PlayerCharac->GetMyGold())
	{
		PlayerCharac->MyCurrentItem->ItemCnt = CurrentCnt + Cnt;
		PlayerCharac->SetMyGold(PlayerCharac->GetMyGold() - (MyCurrentShopItem->ItemPrice) * Cnt);
		PlayerCharac->SaveCharacterStat();
		PlayerCharac->PlaySound("ItemBuy"); // 아이템 구매 효과음 출력
	}
	else
	{
		PlayerCharac->PlaySound("CannotBuy"); // 골드가 모자랄 경우 경고음만 출력
	}
}

void AMyNPCbot::BuyItem2(int32 Cnt)
{
	PlayerCharac->MyCurrentItem = PlayerCharac->MyItemDataTable->FindRow<FItem>(*FString::FromInt(2), TEXT(""));
	int32 CurrentCnt = PlayerCharac->MyCurrentItem->ItemCnt;

	MyCurrentShopItem = MyShopDataTable->FindRow<FShop>(*FString::FromInt(2), TEXT(""));

	if ((MyCurrentShopItem->ItemPrice) * Cnt <= PlayerCharac->GetMyGold())
	{
		PlayerCharac->MyCurrentItem->ItemCnt = CurrentCnt + Cnt;
		PlayerCharac->SetMyGold(PlayerCharac->GetMyGold() - (MyCurrentShopItem->ItemPrice) * Cnt);
		PlayerCharac->SaveCharacterStat();
		PlayerCharac->PlaySound("ItemBuy"); // 아이템 구매 효과음 출력
	}
	else
	{
		PlayerCharac->PlaySound("CannotBuy"); // 골드가 모자랄 경우 경고음만 출력
	}
}