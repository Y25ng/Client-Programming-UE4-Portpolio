// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Inventory_Widget.h"

#include "AController_StartMenu.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/UniformGridSlot.h"
#include "Components/HorizontalBox.h"
#include "Engine.h"
#include "MyBasicCharacter.h"
// #include "UI_ItemSlot_Widget.h"

void UUI_Inventory_Widget::NativeConstruct()
{

	if (Btn_Inventory_Close) 
	{
		Btn_Inventory_Close->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Inventory_CloseWindow);
		// �κ��丮 �ݱ� ��ư ���� �� �ش� �Լ� ȣ��
	}
	if (Btn_ConsumableItem_1)
	{
		Btn_ConsumableItem_1->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Inventory_Use_ConsumableItem_1);
		// �κ��丮 �Һ� ������ ���1 ��� �� ȣ��
	}
	if (Btn_ConsumableItem_2)
	{
		Btn_ConsumableItem_2->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Inventory_Use_ConsumableItem_2);
		// �κ��丮 �Һ� ������ ���2 ��� �� ȣ��
	}
	if (Btn_ConsumableItem_3)
	{
		Btn_ConsumableItem_3->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Inventory_Use_ConsumableItem_3);
		// �κ��丮 �Һ� ������ ���2 ��� �� ȣ��
	}
	if (Btn_ConsumableItem_4)
	{
		Btn_ConsumableItem_4->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Inventory_Use_ConsumableItem_4);
		// �κ��丮 �Һ� ������ ���2 ��� �� ȣ��
	}
	//SpawnSlots();
	if (Btn_Weapon1)
	{
		Btn_Weapon1->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Weapon1_OnEquip);
	}
	if (Btn_Weapon2)
	{
		Btn_Weapon2->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Weapon2_OnEquip);
	}
	if (Btn_Weapon3)
	{
		Btn_Weapon3->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Weapon3_OnEquip);
	}
	if (Btn_Weapon4)
	{
		Btn_Weapon4->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Weapon4_OnEquip);
	}
}


void UUI_Inventory_Widget::Btn_Inventory_CloseWindow() // �κ��丮 �ݱ� ��ư ���� �� ȣ��Ǵ� �Լ�
{
	AAController_StartMenu* contoller = Cast<AAController_StartMenu>(GetOwningPlayer());
	contoller->CloseInventory();
}

void UUI_Inventory_Widget::Btn_Inventory_Use_ConsumableItem_1() // �κ��丮 �Һ� ������ ��� �Լ�
{
	Use_ConsumableItem(1);
}

void UUI_Inventory_Widget::Btn_Inventory_Use_ConsumableItem_2() // �κ��丮 �Һ� ������ ��� �Լ�
{
	Use_ConsumableItem(2);
}

void UUI_Inventory_Widget::Btn_Inventory_Use_ConsumableItem_3() // �κ��丮 �Һ� ������ ��� �Լ�
{
	Use_ConsumableItem(3);
}

void UUI_Inventory_Widget::Btn_Inventory_Use_ConsumableItem_4() // �κ��丮 �Һ� ������ ��� �Լ�
{
	Use_ConsumableItem(4);
}

void UUI_Inventory_Widget::Use_ConsumableItem(int32 Index)
{
	AAController_StartMenu* contoller = Cast<AAController_StartMenu>(GetOwningPlayer());
	contoller->UseConsumableItem(Index);
}

void UUI_Inventory_Widget::Btn_Weapon1_OnEquip()
{
	WeaponChange(0);
}

void UUI_Inventory_Widget::Btn_Weapon2_OnEquip()
{
	WeaponChange(1);
}

void UUI_Inventory_Widget::Btn_Weapon3_OnEquip()
{
	WeaponChange(2);
}

void UUI_Inventory_Widget::Btn_Weapon4_OnEquip()
{
	WeaponChange(3);
}

void UUI_Inventory_Widget::WeaponChange(int32 index)
{
	AAController_StartMenu* contoller = Cast<AAController_StartMenu>(GetOwningPlayer());
	ABasicCharacter* MyCharac = Cast<ABasicCharacter>(contoller->GetPawn());

	if (MyCharac->GetWeaponInventory().Num() - 1 < index) // �ش� ���Կ� ���Ⱑ ���� ��� �ƹ� ���� X
		return;

	if (MyCharac->GetCurrentWeapon() == (MyCharac->GetWeaponInventory())[index]) // ���� �������� ���⸦ ������ ��� �ƹ� ���� X
		return;
	else
	{
		MyCharac->EquipWeapon((MyCharac->GetWeaponInventory())[index]); // ���� �������� ����� �ٸ� ���⸦ ������ ��� ���� ��ü
		AMyBasicCharacter* TempMyCharac = Cast<AMyBasicCharacter>(MyCharac);
		if (TempMyCharac)
			TempMyCharac->PlaySound("WeaponChange"); // ���� ��ü �Ҹ� ���
	}
}

/*
void UUI_Inventory_Widget::SpawnSlots()
{
	AController_StartMenu* controller = Cast<AController_StartMenu>(GetOwningPlayer());

	UUserWidget* slotWidget = controller->uiItemSlotWidget;

	for (int i = 0; i < 8; i++)
	{
		slotWidget = CreateWidget<UUserWidget>(GetWorld());
		GridPanel_ItemSlots->AddChildToGrid(slotWidget);
		MyItemSlot->AddToViewport();
	}





	//GridPanel_ItemSlots->AddChildToGrid(tempWidget);
	//UUniformGridSlot* slotBox = Cast<UUniformGridSlot>(GetWidgetFromName(FName("GridPanel_ItemSlots")));
	//UHorizontalBox* slotBox = Cast<UHorizontalBox>(GetWidgetFromName(FName("HorizontalBox_01")));



	//for (int i = 0; i < 5; i++)
	//{
		//uiItemSlotWidget = CreateWidget<UUserWidget>(GetWorld(), uiItemSlotBPClass);
		//GridPanel_ItemSlots->AddChildToGrid(uiItemSlotWidget);

		//UUserWidget* slotWidget = WidgetTree->ConstructWidget<UUI_ItemSlot_Widget>(MyWidgetClass);

		//slotBox->AddChild(slotWidget);
	//}

	//GridPanel_ItemSlots->AddChildToGrid();


	//static ConstructorHelpers::FClassFinder<UUserWidget> myItemSlot(TEXT("/Game/_My/UI/ItemSlot_BP"));
	//if (myItemSlot.Succeeded())
	//{
	//	uiItemSlotBPClass = myItemSlot.Class;
	//}

	//if (uiItemSlotBPClass)
	//{
	//	uiItemSlotWidget = CreateWidget<UUserWidget>(GetWorld(), uiItemSlotBPClass);
	//	if (uiItemSlotWidget)
	//	{
	//		//if (GridPanel_ItemSlots)
	//		//{
	//		//	GridPanel_ItemSlots->AddChildToGrid(uiItemSlotWidget);
	//		//}
	//		uiItemSlotWidget->AddToViewport();
	//	}
	//}

	//auto GridPanel_ItemSlots = WidgetTree->ConstructWidget<UGridPanel>(UGridPanel::StaticClass());
	//if (GridPanel_ItemSlots)
	//{
	//	auto uiItemSlotBPClass = WidgetTree->ConstructWidget<UUserWidget>(UUserWidget::StaticClass());
	//	GridPanel_ItemSlots->AddChild(uiItemSlotBPClass);
	//}

}
*/
