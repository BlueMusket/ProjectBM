// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_ProjectileNotify.h"
#include "PC.h"
#include "AttackComponent.h"
void UAnim_ProjectileNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation
								  , const FAnimNotifyEventReference& EventReference)
{
 	Super::Notify(MeshComp, Animation, EventReference);

	APC* PC = Cast<APC>(MeshComp->GetOwner());
	if (nullptr == PC)
	{
		return;
	}
	UAttackComponent* AttackComponent = PC->GetComponentByClass<UAttackComponent>();

	if (nullptr != AttackComponent)
	{
		//AttackComponent->OnThrow();
	}
}