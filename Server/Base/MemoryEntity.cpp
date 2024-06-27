#include "MemoryEntity.h"
#include "AllocComponent.h"

CMemoryEntity::CMemoryEntity()
{
	// 기본 Component  설정
	InsertComponent<CAllocComponent>();
}

CMemoryEntity::~CMemoryEntity()
{

}
