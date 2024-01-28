// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_ProjectileNotify.h"
#include "PC.h"

void UAnim_ProjectileNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation
								  , const FAnimNotifyEventReference& EventReference)
{
 	Super::Notify(MeshComp, Animation, EventReference);

	APC* Pc = Cast<APC>(MeshComp->GetOwner());
	if (nullptr == Pc)
	{
		return;
	}

	Pc->SpawnProjectile();
}