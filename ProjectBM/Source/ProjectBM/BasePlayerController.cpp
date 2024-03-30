// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "RestartWidget.h"
#include "HUDWidget.h"
#include "AdminWidget.h"
#include "BaseCharacter.h"
#include "PCEntryInfo.h"
#include "WidgetContextComponent.h"
#include "Net/UnrealNetwork.h"
#include "PCState.h"

ABasePlayerController::ABasePlayerController(const FObjectInitializer& ObjectInitializer/* = FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
{
	// 리플리케이션 활성화
	bReplicates = true;
	WidgetContext = CreateDefaultSubobject<UWidgetContextComponent>(TEXT("WidgetContext"));

	// PCEntryInfo 인스턴스 생성 및 초기화
	//if (HasAuthority())
	{
		PCEntryInfo = NewObject<UPCEntryInfo>();
	}
}

void ABasePlayerController::Deserialize(int NewSessionId, int NewPartyId, int NewUserId)
{
	PCEntryInfo->Deserialize(NewSessionId, NewPartyId, NewUserId);
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);


	if (IsLocalPlayerController())
	{
		if (nullptr != BP_HUDWidget)
		{
			HUDWidget = CreateWidget<UHUDWidget>(this, BP_HUDWidget);
			if (nullptr != HUDWidget)
			{
				HUDWidget->AddToViewport();
			}
		}
	}

	//ENetRole MyLocalRole = GetLocalRole();
	//ENetRole MyRemoteRole = GetRemoteRole();
}

void ABasePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (nullptr != PCEntryInfo)
	{
		const FString SessionIdStr = FString::Printf(TEXT("SessionId : %d"), PCEntryInfo->GetSessionId());

		ABaseCharacter* BaseCharacter = GetPawn<ABaseCharacter>();

		if (!IsValid(BaseCharacter))
		{
			return;
		}

		FVector Location = BaseCharacter->GetActorLocation();

		ENetRole MyLocalRole = GetLocalRole();

		if (ENetRole::ROLE_Authority == MyLocalRole) // 서버
		{
			Location.Z += 10;
			DrawDebugString(GetWorld(), Location, SessionIdStr, nullptr, FColor::Red, 0.0f, true);
		}
		else // 클라이언트
		{
			DrawDebugString(GetWorld(), Location, SessionIdStr, nullptr, FColor::White, 0.0f, true);
		}
	}
}

FVector ABasePlayerController::OnScreenLocationFromMouse()
{
	float MouseX, MouseY;
	FVector OutLocation;
	if (GetMousePosition(MouseX, MouseY))
	{
		FVector CursorLocation, CursorDirection;

		if (DeprojectScreenPositionToWorld(MouseX, MouseY, CursorLocation, CursorDirection))
		{
			// 카메라 위치에서 마우스가 가리키는 방향으로 레이를 쏴서 X = PlaneX 평면과의 교차점을 찾습니다.
			// 레이의 방정식: P = WorldLocation + t * WorldDirection
			// 교차점에서 X = PlaneX 이므로, t = (PlaneX - WorldLocation.X) / WorldDirection.X
			// OutLocation은 이제 X = 0 평면에서 마우스 위치에 해당하는 월드 좌표입니다.
			if (FMath::Abs(CursorDirection.X) > KINDA_SMALL_NUMBER) // 0으로 나누는 것을 방지
			{
				float t = (0 - CursorLocation.X) / CursorDirection.X;
				OutLocation = CursorLocation + t * CursorDirection;
			}
		}
	}

	return OutLocation;
}

void ABasePlayerController::UpdateHealthPercent(float HealthPercent)
{
	//WidgetContext->UpdateHealthPercent(HealthPercent);

	if (!IsLocalPlayerController())
	{
		return;
	}

	if (nullptr != HUDWidget)
	{
		HUDWidget->UpdateHealthPercent(HealthPercent);
	}
}

void ABasePlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// EntryInfo의 리플리케이션 설정
	DOREPLIFETIME(ABasePlayerController, PCEntryInfo);
}

// Server only
void ABasePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//AGDPlayerState* PS = GetPlayerState<AGDPlayerState>();
	//if (PS)
	//{
	//	// Init ASC with PS (Owner) and our new Pawn (AvatarActor)
	//	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	//}

	UpdateHealthPercent(100.f);
}


void ABasePlayerController::OnRep_EntryInfo()
{

}

void ABasePlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// For edge cases where the PlayerState is repped before the Hero is possessed.
	// CreateHUD();
}
