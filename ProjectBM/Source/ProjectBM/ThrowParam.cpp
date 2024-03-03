// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowParam.h"
#include "PC.h"
#include "BasePlayerController.h"

FThrowParam::FThrowParam()
	: SpawnLocation(FVector())
	, ThrowRotation(FRotator())
	, MaxPower(10000.f)
	, PowerIncreaseRate(10.f)
	, ThrowPower(0.f)
	, IsValid(false)
{

}

FThrowParam::~FThrowParam()
{

}


bool FThrowParam::Serialize(APC* PC)
{
	bool result = false;

	do
	{
		if (nullptr == PC)
		{
			break;
		}

		ABasePlayerController* Controller = PC->GetController<ABasePlayerController>();
		if (nullptr == Controller)
		{
			break;
		}

		// spawnLocation 처리
		{
			SpawnLocation = PC->GetMesh()->GetSocketLocation(FName("ProjectileSocket"));
			SpawnLocation.X = 0.f;
		}

		// rotation처리
		{
			// 마우스 위치를 저장할 변수
			float MouseX, MouseY;
			Controller->GetThrowMousePos(MouseX, MouseY);
			FVector CursorLocation, CursorDirection;
			FVector OutLocation;

			if (Controller->DeprojectScreenPositionToWorld(MouseX, MouseY, CursorLocation, CursorDirection))
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

			// 발사 방향 계산
			FVector Direction = (OutLocation - SpawnLocation).GetSafeNormal();
			ThrowRotation = Direction.Rotation();
		}

		result = true;
	} while (false);

	return result;
}