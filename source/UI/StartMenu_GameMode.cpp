// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu_GameMode.h"
#include "StartMenu_HUD.h"
#include "AController_StartMenu.h"


AStartMenu_GameMode::AStartMenu_GameMode()
{
	HUDClass = AStartMenu_HUD::StaticClass(); // 게임모드의 HUD 클래스 지정
	DefaultPawnClass = nullptr; 
	PlayerControllerClass = nullptr;

}

