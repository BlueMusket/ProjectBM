#pragma once

/// <summary>
/// 관리가 필요한 클래스의 부모 클래스
/// </summary>
class CObject
{
protected:
	virtual bool CanDelete();
	static void SafeDelete(CObject* object);
};

